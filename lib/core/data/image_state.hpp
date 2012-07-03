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
 * image_state.hpp
 *
 * Description:
 *
 *  Created on: Jun 8, 2012
 *      Author: tuerke
 ******************************************************************/
#ifndef _ISIS_GLANCE_IMAGE_STATE_HPP
#define _ISIS_GLANCE_IMAGE_STATE_HPP

#include <CoreUtils/vector.hpp>
#include "image_properties.hpp"

namespace isis
{
namespace glance
{
namespace data
{

/**
 * ImageState combines all the properties of an
 * image that need to have fast access to read and write.
 */

class ImageState
{
public:
	ImageState( const isis::data::Image &image );

	///The current coordinates we are looking at in image space
	isis::util::ivector4 voxel_coords;

	///The current coordinates we are looking at in physical space
	isis::util::ivector4 physical_coords;

	///Is this image visible?
	bool is_visible;

	///Is this image valid?
	bool is_valid;
protected:
	ImageState() {}
};

} // end namespace data
} // end namespace glance
} // end namespace isis


#endif // _ISIS_GLANCE_IMAGE_STATE_HPP