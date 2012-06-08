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
 * image_container.hpp
 *
 * Description:
 *
 *  Created on: Jun 8, 2012
 *      Author: tuerke
 ******************************************************************/

#ifndef _ISIS_GLANCE_IMAGE_CONTAINER_HPP
#define _ISIS_GLANCE_IMAGE_CONTAINER_HPP

#include "image.hpp"

namespace isis {
namespace glance {

class ImageContainer
{
	/**
	 * Add an isis::glance::Image to the widget
	 * \return True if adding was successsful.
	 */
	virtual bool addImage( const Image::Pointer image );

	/**
	 * Add a list of isis::glance::Image to the widget
	 * \return True if adding was successsful.
	 */
	virtual bool addImages( const Image::Vector &images );
};
	

} // end namespace glance
} // end namespace isis


#endif