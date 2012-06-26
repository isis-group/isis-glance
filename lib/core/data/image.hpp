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
 *  Created on: Jun 26, 2012
 *      Author: tuerke
 ******************************************************************/
#ifndef _ISIS_GLANCE_IMAGE_HPP
#define _ISIS_GLANCE_IMAGE_HPP

#include "image_base.hpp"

namespace isis {
namespace glance {
namespace data {

class Image : public ImageBase
{
public:
	/**
	 * Creates an isis::glance::data::Image from an existing isis::data::Image.
	 * \param image The isis::data::Image
	 * \param force_typed_image If true the isis::glance::data::Image will ensure to have volumes of consistent data type.
	 */
	Image( const isis::data::Image &image, bool force_typed_image = false );

	/**
	 * Creates an isis::glance::data::Image from an existing isis::data::Image with specified type_id.
	 * \param image The isis::data::Image
	 * \param type_id The type ID that specifies the type of each volume.
	 */	
	Image( const isis::data::Image &image, const ImageDataType &type_id );
	
	/**
	 * Copies the data from the isis::data::Image into
	 * the isis::glance::Image.
	 * This is done by creating a memory copy of the images data
	 * into contiguous space and then splicing it to get
	 * a vector representing the number of volumes/timesteps
	 * of the isis::data::Image .
	 * \param image The isis::data::Image
	 * \param content Specifies which type of content should be synchronized
	 * \return True if synchronizing was successful.
	 * Otherwise returns false.
	 */
	bool synchronizeFrom( const isis::data::Image &image, const ImageContentType &content );

	bool synchronize( const ImageContentType &content ) { return synchronizeFrom( *isis_image_, content ); }

	void setDataType( const ImageDataType &type ) { type_ = type; force_typed_image_ = true; }

protected:
	bool synchronizeVoxelContentFrom( isis::data::Image image );
	void convertVolumesByType( const ImageDataType &type );
private:
	//we need to hold those properties for future calls of synchronizeVoxelContentFrom
	bool force_typed_image_;
	ImageDataType type_;
};
	
} // end namespace data
} // end namespace glance
} // end namespace isis


#endif // _ISIS_GLANCE_IMAGE_HPP