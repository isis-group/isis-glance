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
#include <DataStorage/valuearray.hpp>

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

	///Returns the underlying isis image.
	const data::Image &get() const { return isis_image_; }

	void synchronizeFrom( const data::Image &image );

private:
	const data::Image &isis_image_;

	template<typename T>
	void _synchronizeFrom( const isis::data::Image &image ) {
		isis::data::ValueArray<T> imagePtr( ( T * ) calloc( image.getVolume(), sizeof( T ) ), image.getVolume() );
		image.copyToMem<T>( &imagePtr[0], image.getVolume() );
		BOOST_FOREACH( std::vector< isis::data::ValueArrayReference >::const_reference volume, imagePtr.splice( image_size[0] * image_size[1] * image_size[2] ) ) {
			push_back( isis::data::Chunk( volume, image_size[0], image_size[1], image_size[2] ) );
		}
		assert( size() == static_cast<uint32_t>( image_size[isis::data::timeDim] ) );
	}
	


};
} // end namespace glance
} // end namespace isis

#endif // _ISIS_GLANCE_IMAGE_HPP
