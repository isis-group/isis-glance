/****************************************************************
 *
 * <Copyright information>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 3
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 *
 * Author: Erik Tuerke, etuerke@googlemail.com
 *
 * image.cpp
 *
 * Description:
 *
 *  Created on: Jun 26, 2012
 *      Author: tuerke
 ******************************************************************/

#include "image.hpp"
#include "util/signal.hpp"
#include "common.hpp"

namespace isis
{
namespace glance
{
namespace data
{

bool Image::forceProposedDataType_ = false;

util::Signal<void( const Image &, const types::ImageDataType & )> Image::signal_conversion_begin;
util::Signal<void( const Image &, const types::ImageDataType & )> Image::signal_conversion_end;
util::Signal<void( const Image &, const Image::ImageContentType & )> Image::signal_content_changed;

types::ImageDataType Image::proposedScalar_ = types::SCALAR_PROPOSED;
types::ImageDataType Image::proposedColor_ = types::COLOR_PROPOSED;
types::ImageDataType Image::proposedComplex_ = types::COMPLEX_PROPOSED;
types::ImageDataType Image::proposedVector_ = types::VECTOR_PROPOSED;

Image::Image ( const isis::data::Image &image )
	: ImageBase ( image ),
	  type_( major_type )
{
	if( forceProposedDataType_ ) {
		switch( type_group ) {
		case SCALAR:
			type_ = proposedScalar_;
			break;
		case COLOR:
			type_ = proposedColor_;
			break;
		case COMPLEX:
			type_ = proposedComplex_;
			break;
		case VECTOR:
			type_ = proposedVector_;
			break;
		}
	}

	is_valid = synchronizeVoxelContentFrom( image );

	if( !is_valid ) {
		LOG( Runtime, error ) << "Creating of isis::glance::Image from "
							  << file_path << " failed!";
	}
}


Image::Image ( const isis::data::Image &image, const types::ImageDataType &type )
	: ImageBase ( image ),
	  type_( type )
{
	is_valid = synchronizeVoxelContentFrom( image );

	if( !is_valid ) {
		LOG( data::Runtime, error ) << "Creating of isis::glance::Image from "
									<< file_path << " failed!";
	}
}


void Image::setProposedDataType ( const ImageDataProperties::ImageTypeGroup &type_group, const types::ImageDataType &data_type )
{
	switch( type_group ) {
	case SCALAR:
		proposedScalar_ = data_type;
		break;
	case COLOR:
		proposedColor_ = data_type;
		break;
	case COMPLEX:
		proposedComplex_ = data_type;
		break;
	case VECTOR:
		proposedVector_ = data_type;
		break;
	}
}


void Image::convertVolumesByType ( const types::ImageDataType &type )
{
	signal_conversion_begin( *this, type );
	LOG( Runtime, info ) << "Converting image " << file_path << " to type "
						 << isis::util::getTypeMap( false ).at( type );
	VolumesType buffer;
	const size_t volume_size[] = { image_size[0], image_size[1], image_size[2] };
	BOOST_FOREACH( VolumesType::reference volume, volumes_ ) {
		buffer.push_back( VolumeType( volume->convertByID( type ), volume_size ) );
	}
	assert( buffer.size() == volumes_.size() );
	volumes_ = buffer;
	signal_conversion_end( *this, type );
}


bool Image::synchronizeFrom ( const isis::data::Image &image, const ImageBase::ImageContentType &content )
{
	bool ok = true;

	switch( content ) {
	case PROPERTIES_META:
	case PROPERTIES_DATA:
	case STATE:
		ok = ok && synchronizeMetaContentFrom( image, content );
		break;
	case ALL:
		ok = ok && synchronizeVoxelContentFrom( image );
		ok = ok && synchronizeMetaContentFrom( image, content );
		break;
	case VOXELS:
		ok = ok && synchronizeVoxelContentFrom( image );
		ok = ok && synchronizeMetaContentFrom( image, PROPERTIES_DATA );
		break;
	}

	//send signal if synchronization was successful
	if( ok ) {
		signal_content_changed( *this, content );
	}

	return ok;
}

bool Image::synchronizeVoxelContentFrom ( isis::data::Image image )
{
	volumes_.clear();
	//since we want to have size[timeDim] volumes we have to splice the image
	image.spliceDownTo( isis::data::timeDim );

	if( !has_one_type || forceProposedDataType_ ) {
		LOG_IF( !has_one_type, Runtime, info ) << "Image " << file_path << " has more than one data type. Converting it to the major data type ("
											   << isis::util::getTypeMap( false ).at( type_ ) << ").";
		LOG_IF( forceProposedDataType_, Runtime, info ) << "Converting " << file_path << " to proposed data type "
				<< isis::util::getTypeMap( false ).at( type_ );

		if( !image.convertToType( type_ ) ) {
			LOG( Runtime, error ) << "Conversion of " << file_path << " to type "
								  << isis::util::getTypeMap( false ).at( type_ ) << " failed.";
			return false;
		};
	}

	const size_t volume[] = { image_size[0], image_size[1], image_size[2] };

	std::vector<isis::data::Chunk> chunks = image.copyChunksToVector( false );

	if( chunks.size() == image_size[isis::data::timeDim] ) {
		BOOST_FOREACH( std::vector<isis::data::Chunk>::reference chunk, chunks ) {
			volumes_.push_back( VolumeType( chunk.asValueArrayBase(), volume ) );
		}
	} else {
		LOG( data::Runtime, isis::info ) << "The number of chunks (" << chunks.size()
										 << ") does not coincide with the number of timesteps (" << image_size[isis::data::timeDim]
										 << ") of image " << file_path << ". Will copy data to contiguous memory.";

		//the image is spliced at sliceDim
		if( chunks.size() ==  image_size[isis::data::timeDim] * image_size[isis::data::sliceDim] ) {
			for( size_t timestep = 0; timestep < image_size[isis::data::timeDim]; timestep++ ) {
				isis::data::Chunk chunk = chunks.front().cloneToNew( image_size[isis::data::rowDim],
										  image_size[isis::data::columnDim],
										  image_size[isis::data::sliceDim] );

				for( size_t slice = 0; slice < image_size[isis::data::sliceDim]; slice++ ) {
					const size_t index = slice + timestep * image_size[isis::data::sliceDim];
					isis::data::Chunk &tmpChunk = chunks[index];
					tmpChunk.copySlice( 0, 0, chunk, slice, 0 );
				}

				volumes_.push_back( VolumeType( chunk.asValueArrayBase(), volume ) );
			}
		} else {
			LOG( data::Runtime, isis::error ) << "Image " << file_path << " is spliced below sliceDim. "
											  << "This is not supported yet!";
			return false;
		}
	}

	return volumes_.size() == image_size[isis::data::timeDim];
}




} // end namespace data
} // end namespace glance
} // end namespace isis