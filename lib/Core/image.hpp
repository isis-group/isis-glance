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
 * image.hpp
 *
 * Description:
 *
 *  Created on: Jun 8, 2012
 *      Author: tuerke
 ******************************************************************/
#ifndef _ISIS_GLANCE_IMAGE_HPP
#define _ISIS_GLANCE_IMAGE_HPP

#include <DataStorage/chunk.hpp>
#include <DataStorage/image.hpp>

#include <boost/shared_ptr.hpp>
#include <vector>

#include "image_state.hpp"
#include "image_properties.hpp"

namespace isis
{
namespace glance
{

class Image
	: public ImageState,
  public ImageProperties,
  protected std::vector<isis::data::Chunk>
{
public:
	Image( const isis::data::Image &image );


};
} // end namespace glance
} // end namespace isis

#endif // _ISIS_GLANCE_IMAGE_HPP