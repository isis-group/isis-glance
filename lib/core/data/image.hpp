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

namespace isis
{
namespace glance
{
namespace data
{

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
	 * Creates an isis::glance::data::Image from an existing isis::data::Image with specified type.
	 * \param image The isis::data::Image
	 * \param type The type that specifies the type of each volume.
	 */
	Image( const isis::data::Image &image, const types::ImageDataType &type );

	/**
	 * Synchronizes the isis::glance::data::Image with the isis::data::Image
	 * specified by image.
	 * \param image The isis::data::Image that should be used for synchronizing.
	 * \param content Type of content that should be synchronized.
	 * \return True if synchronizing was successful. Otherwise returns false.
	 */
	bool synchronizeFrom( const isis::data::Image &image, const ImageContentType &content );

	/**
	 * Synchronizes the isis::glance::data::Image with the underlying isis::data::Image
	 * that can be accessed by the get() method.
	 * \param content Type of content that should be synchronized.
	 * \return True if synchronizing was successful. Otherwise false.
	 */
	bool synchronize( const ImageContentType &content ) { return synchronizeFrom( *isis_image_, content ); }

	/**
	 * Sets the data type that should be used for synchronizing of voxel content.
	 * \param type The data type used to synchronize.
	 * \note This method also calls the setForceTypedImage( true ).
	 */
	void setDataType( const types::ImageDataType &type ) { type_ = type; force_typed_image_ = true; }
	
	types::ImageDataType getDataType() const { return type_; }
	
	/**
	 * An isis::data::Image can consist of chunks with different data type.
	 * If setForceTypedImage is set to true the isis::glance::data::Image will ensure
	 * to all volumes to have one image type. This can either be the major_type if no
	 * data type was specified or the data type specified by one of the respective functions.
	 * \param force Specifies if the image should ensure consistent data type.
	 */
	void setForceTypedImage( bool force ) { force_typed_image_ = force; }

protected:
	bool synchronizeVoxelContentFrom( isis::data::Image image );
	void convertVolumesByType( const types::ImageDataType &type );
private:
	//we need to hold these properties for future calls of synchronize and synchronizeFrom
	bool force_typed_image_;
	types::ImageDataType type_;
};

} // end namespace data
} // end namespace glance
} // end namespace isis


#endif // _ISIS_GLANCE_IMAGE_HPP