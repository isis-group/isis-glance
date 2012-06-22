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
 * image_state.cpp
 *
 * Description:
 *
 *  Created on: Jun 11, 2012
 *      Author: tuerke
 ******************************************************************/
#include "image_state.hpp"

namespace isis
{
namespace glance
{
namespace data
{
ImageState::ImageState ( const isis::data::Image &image )
	: is_visible( true ),
	  is_valid( false )
{
	voxel_coords = image.getSizeAsVector() / 2;
	voxel_coords[isis::data::timeDim] = 0;
	physical_coords = image.getPhysicalCoordsFromIndex( voxel_coords );
}

} // end namespace data
} // end namespace glance
} // end namespace isis