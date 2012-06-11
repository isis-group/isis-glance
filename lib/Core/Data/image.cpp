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
#include "../common.hpp"

namespace isis
{
namespace glance
{

Image::Image ( const isis::data::Image &image )
	: ImageState( image ),
	  ImageProperties( image ),
	  isis_image_( image )
{
	synchronizeFrom( image );

}

void Image::synchronizeFrom( const data::Image &image )
{
	if( type_group == SCALAR ) {
		_synchronizeFrom<InternalDataRepresentationScalar>( image );
	} else if ( type_group == COLOR ) {
		_synchronizeFrom<InternalDataRepresentationColor>( image );
	}
}



} // end namespace glance
} // end namespace isis