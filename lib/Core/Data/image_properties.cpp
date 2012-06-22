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
#include "../geometrical.hpp"

#include <boost/filesystem.hpp>

namespace isis
{
namespace glance
{
namespace data
{

ImageProperties::ImageProperties()
{}

ImageProperties::ImageProperties ( const isis::data::Image &image )
{
	//setting all the needed properties from the image
	const std::pair<util::ValueReference, util::ValueReference> _min_max = image.getMinMax();
	major_type_id = getMajorTypeID( _min_max );
	has_one_typeid = getHasOneType( image );

	if( isis::data::ValueArray<util::color24>::staticID == major_type_id || isis::data::ValueArray<util::color48>::staticID == major_type_id ) {
		type_group = COLOR;
	} else if ( isis::data::ValueArray<std::vector< float > >::staticID == major_type_id || isis::data::ValueArray<std::vector< double > >::staticID == major_type_id ) {
		type_group = COMPLEX;
	} else if (     isis::data::ValueArray<util::ivector4>::staticID == major_type_id ||
					isis::data::ValueArray<util::fvector4>::staticID == major_type_id ||
					isis::data::ValueArray<util::dvector4>::staticID == major_type_id ) {
		type_group = VECTOR;
	} else {
		type_group = SCALAR;
		min_max = std::make_pair<double, double>( _min_max.first->as<double>(), _min_max.second->as<double>() );
		extent = min_max.second - min_max.first;
	}

	//geometrical stuff
	image_size = image.getSizeAsVector();
	image_size_aligned32 = geometrical::get32BitAlignedSize( image_size );
	orientation_matrix = geometrical::getOrientationMatrixFromPropMap( image );
	orientation_matrix_latched = geometrical::getLatchedOrienation( orientation_matrix );
	voxel_size = image.getPropertyAs<util::fvector4>( "voxelSize" );

	if( image.hasProperty( "voxelGap" ) ) {
		voxel_size += image.getPropertyAs<util::fvector4>( "voxelGap" ) ;
	}

	if( image.hasProperty( "file_path" ) ) {
		boost::filesystem::path p( image.getPropertyAs<std::string>( "file_path" ) );
		file_name = p.filename();
		file_path = p.directory_string();
	}
}


short unsigned int ImageProperties::getMajorTypeID( const std::pair<util::ValueReference, util::ValueReference> &_min_max ) const
{
	if( _min_max.first->getTypeID() == _min_max.second->getTypeID() ) { // ok min and max are the same type - trivial case
		return _min_max.first->getTypeID() << 8; // btw: we do the shift, because min and max are Value - but we want the ID's ValuePtr
	} else if( _min_max.first->fitsInto( _min_max.second->getTypeID() ) ) { // if min fits into the type of max, use that
		return _min_max.second->getTypeID() << 8; //@todo maybe use a global static function here instead of a obscure shit operation
	} else if( _min_max.second->fitsInto( _min_max.first->getTypeID() ) ) { // if max fits into the type of min, use that
		return _min_max.first->getTypeID() << 8;
	} else {
		LOG( isis::util::Runtime, error ) << "Sorry I dont know which datatype I should use. (" << _min_max.first->getTypeName()
										  << " or " << _min_max.second->getTypeName() << ")";
	}

	return 0;

}

bool ImageProperties::getHasOneType( const isis::data::Image &image ) const
{
	//iterate through all the chunks and check if there is one chunk whose image type is different from the major_type_id
	BOOST_FOREACH( std::list<isis::data::Chunk>::const_reference chunk, image.copyChunksToVector( false ) ) {
		if( chunk.getTypeID() != major_type_id ) {
			return false;
		}
	}
	return true;
}

} // end namespace data
} // end namespace glance
} // end namespace isis