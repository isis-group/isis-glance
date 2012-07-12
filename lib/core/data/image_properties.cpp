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
 * image_properties.cpp
 *
 * Description:
 *
 *  Created on: Jun 8, 2012
 *      Author: tuerke
 ******************************************************************/
#include "image_properties.hpp"
#include "util/geometrical.hpp"
#include "common.hpp"

#include <boost/filesystem.hpp>

namespace isis
{
namespace glance
{
namespace data
{


ImageDataProperties::ImageDataProperties ( const isis::data::Image &image )
{
	//setting all the needed properties from the image
	const std::pair<isis::util::ValueReference, isis::util::ValueReference> _min_max = image.getMinMax();
	major_type = getMajorType( _min_max );
	has_one_type = getHasOneType( image );

	if( types::COLOR_24 == major_type || types::COLOR_48 == major_type ) {
		type_group = COLOR;
	} else if ( types::COMPLEX_FLOAT == major_type || types::COMPLEX_DOUBLE == major_type ) {
		type_group = COMPLEX;
	} else if (     types::VECTOR4_FLOAT == major_type ||
					types::VECTOR4_DOUBLE == major_type ||
					types::VECTOR4_INT == major_type ) {
		type_group = VECTOR;
	} else {
		type_group = SCALAR;
		min_max = std::make_pair<double, double>( _min_max.first->as<double>(), _min_max.second->as<double>() );
		extent = min_max.second - min_max.first;
	}
}


types::ImageDataType ImageDataProperties::getMajorType( const std::pair<isis::util::ValueReference, isis::util::ValueReference> &_min_max ) const
{
	if( _min_max.first->getTypeID() == _min_max.second->getTypeID() ) { // ok min and max are the same type - trivial case
		return static_cast<types::ImageDataType>( _min_max.first->getTypeID() << 8 ); // btw: we do the shift, because min and max are Value - but we want the ID's ValuePtr
	} else if( _min_max.first->fitsInto( _min_max.second->getTypeID() ) ) { // if min fits into the type of max, use that
		return static_cast<types::ImageDataType>( _min_max.second->getTypeID() << 8 ); //@todo maybe use a global static function here instead of a obscure shit operation
	} else if( _min_max.second->fitsInto( _min_max.first->getTypeID() ) ) { // if max fits into the type of min, use that
		return static_cast<types::ImageDataType>( _min_max.first->getTypeID() << 8 );
	} else {
		LOG( isis::glance::data::Runtime, error ) << "Sorry I dont know which datatype I should use. (" << _min_max.first->getTypeName()
				<< " or " << _min_max.second->getTypeName() << ")";
	}

	return types::UNDEFINED;

}

bool ImageDataProperties::getHasOneType( const isis::data::Image &image ) const
{
	//iterate through all the chunks and check if there is one chunk whose image type is different from the major_type_id
	BOOST_FOREACH( std::list<isis::data::Chunk>::const_reference chunk, image.copyChunksToVector( false ) ) {
		if( static_cast<types::ImageDataType>( chunk.getTypeID() ) != major_type ) {
			return false;
		}
	}
	return true;
}



ImageMetaProperties::ImageMetaProperties ( const isis::data::Image &image )
{
	//geometrical stuff
	image_size = image.getSizeAsVector();
	image_size_aligned32 = util::get32BitAlignedSize( image_size );
	orientation_matrix = util::getOrientationMatrixFromPropMap( image );
	orientation_matrix_latched = util::getLatchedOrienation( orientation_matrix );
	voxel_size = image.getPropertyAs<isis::util::fvector4>( "voxelSize" );

	if( image.hasProperty( "voxelGap" ) ) {
		voxel_size += image.getPropertyAs<isis::util::fvector4>( "voxelGap" ) ;
	}

	if( image.hasProperty( "file_path" ) ) {
		boost::filesystem::path p( image.getPropertyAs<std::string>( "file_path" ) );
		file_name = p.filename();
		file_path = p.directory_string();
	}
	Volume::size_type volSize;
	volSize[0] = image_size[0];
	volSize[1] = image_size[1];
	volSize[2] = image_size[2];
	permutation_sagittal = DataHandler::getPermutationSagittal( volSize );
}




} // end namespace data
} // end namespace glance
} // end namespace isis