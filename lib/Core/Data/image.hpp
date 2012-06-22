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
#include <boost/signals2.hpp>
#include <vector>

#include "image_state.hpp"
#include "image_properties.hpp"
#include "common.hpp"

namespace isis
{
namespace glance
{
namespace data
{

class Image
	: public ImageState,
  public ImageProperties,
  private std::vector<isis::data::Chunk>
{
public:
	enum ImageContentType { VOXEL_CONTENT, PROPERTY_CONTENT, STATE_CONTENT };

	Image( const isis::data::Image &image );

	///Returns the underlying isis image.
	const isis::data::Image &get() const { return *isis_image_; }

	/**
	 * Copies the data from the isis::data::Image into
	 * the isis::glance::Image.
	 * This is done by creating a memory copy of the images data
	 * into contiguous space and then splicing it to get
	 * a vector representing the number of volumes/timesteps
	 * of the isis::data::Image .
	 * \param image The isis::data::Image
	 * \return True if synchronizing was successful.
	 * Otherwise returns false.
	 */
	bool synchronizeFrom( const isis::data::Image &image );


	isis::data::Chunk &operator[]( size_type const &index ) {
		return std::vector<isis::data::Chunk>::operator[]( index );
	}
	const isis::data::Chunk &operator[]( size_type const &index ) const {
		return std::vector<isis::data::Chunk>::operator[]( index );
	}

	size_type size() const {
		return std::vector<isis::data::Chunk>::size();
	}

	//signals
	boost::signals2::signal<void ( const ImagePointer &, const ImageContentType & )> signal_image_changed_content;
private:
	const IsisImagePointer isis_image_;

	//do not allow to copy a glance::data::Image
	Image( const Image & );

	/// @cond _internal
	API_EXCLUDE_BEGIN
	template<typename T>
	bool _synchronizeFrom( const isis::data::Image &image ) {
		isis::data::ValueArray<T> imagePtr( ( T * ) calloc( image.getVolume(), sizeof( T ) ), image.getVolume() );
		//copy the images data into a contiguous volume of type T
		image.copyToMem<T>( &imagePtr[0], image.getVolume() );
		LOG( isis::data::Debug, info ) << "Created memcopy of size " << ( image.getVolume() * sizeof( T ) ) / ( 1024. * 1024. )
									   << " mb for image " << file_path;

		BOOST_FOREACH( std::vector< isis::data::ValueArrayReference >::const_reference volume, imagePtr.splice( image_size[0] * image_size[1] * image_size[2] ) ) {
			push_back( isis::data::Chunk( volume, image_size[0], image_size[1], image_size[2] ) );
		}

		if( size() != static_cast<uint32_t>( image_size[isis::data::timeDim] ) ) {
			LOG( isis::data::Runtime, error ) << "The number of chunks (" << size()
											  << ") does not coincide with the number of volumes of the image "
											  << file_path << " (" << image_size[isis::data::timeDim] << ").";
			return false;
		}

		signal_image_changed_content( ImagePointer( this ) , VOXEL_CONTENT );
		return true;
	}
	API_EXCLUDE_END
	/// @endcond _internal


};
} // end namespace data
} // end namespace glance
} // end namespace isis

#endif // _ISIS_GLANCE_IMAGE_HPP
