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
 * image_base.cpp
 *
 * Description:
 *
 *  Created on: Jun 8, 2012
 *      Author: tuerke
 ******************************************************************/
#include "image_base.hpp"
#include "common.hpp"

namespace isis
{
namespace glance
{
namespace data
{

ImageBase::ImageBase ( const isis::data::Image &image )
	: ImageState( image ),
	  ImageDataProperties( image ),
	  ImageMetaProperties( image ),
	  isis_image_(  image )
{}

//private constructor
ImageBase::ImageBase ( const ImageBase & )
	: ImageState(),
	ImageDataProperties(),
	ImageMetaProperties()
{}


bool ImageBase::synchronizeMetaContentFrom( const isis::data::Image &image, const ImageBase::ImageContentType &content )
{
	switch( content ) {
	case PROPERTIES_META:
		static_cast<ImageMetaProperties &>( *this ) = image;
		break;
	case PROPERTIES_DATA:
		static_cast<ImageDataProperties &>( *this ) = image;
		break;
	case STATE:
		static_cast<ImageState &>( *this ) = image;
		break;
	case ALL:
		static_cast<ImageMetaProperties &>( *this ) = image;
		static_cast<ImageDataProperties &>( *this ) = image;
		static_cast<ImageState &>( *this ) = image;
		break;
	default:
		break;
	}
	return true;
}




} // end namespace data
} // end namespace glance
} // end namespace isis