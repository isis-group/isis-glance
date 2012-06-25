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
 *  Created on: Jun 8, 2012
 *      Author: tuerke
 ******************************************************************/
#include "image.hpp"
#include "common.hpp"
#include "util/signals.hpp"

namespace isis
{
namespace glance
{
namespace data
{

Image::Image ( const isis::data::Image &image )
	: ImageState( image ),
	  ImageProperties( image ),
	  isis_image_(  image )
{
	is_valid =  synchronizeFrom( image, Image::CONTENT_VOXEL );

	if ( !is_valid ) {
		LOG( isis::data::Runtime, error ) << "Creating of isis::glance::Image from "
										  << file_path << " failed!";
	}
}

Image::Image ( const glance::data::Image & )
	: ImageState(),
	  ImageProperties()
{}


bool Image::synchronizeFrom( const isis::data::Image &image, const Image::ImageContentType &content )
{
	bool return_value = true;

	switch( content ) {
	case CONTENT_PROPERTIES:
		static_cast<ImageProperties &>( *this ) = image;
		break;
	case CONTENT_STATE:
		static_cast<ImageState &>( *this ) = image;
		break;
	case CONTENT_VOXEL:
		return_value = _synchronizeVoxelContentFrom( image );
		break;
	case CONTENT_ALL: {
		static_cast<ImageProperties &>( *this ) = image;
		static_cast<ImageState &>( *this ) = image;
		return_value = return_value && _synchronizeVoxelContentFrom( image );
		break;
	}
	}

	signal::image_content_changed( this, content );
	return return_value;
}

bool Image::_synchronizeVoxelContentFrom ( const isis::data::Image &image )
{
	volumes_.clear();

	switch( type_group ) {
	case SCALAR:
		return _synchronizeFrom<ScalarRepn>( image );
		break;
	case COLOR:
		return _synchronizeFrom<ColorRepn>( image );
		break;
	case VECTOR:
		return _synchronizeFrom<VectorRepn>( image );
		break;
	case COMPLEX:
		return _synchronizeFrom<ComplexRepn>( image );
		break;
	}
}


} // end namespace data
} // end namespace glance
} // end namespace isis