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
 * image_base.hpp
 *
 * Description:
 *
 *  Created on: Jun 8, 2012
 *      Author: tuerke
 ******************************************************************/
#ifndef _ISIS_GLANCE_IMAGE_BASE_HPP
#define _ISIS_GLANCE_IMAGE_BASE_HPP

#include <DataStorage/chunk.hpp>
#include <DataStorage/image.hpp>
#include <DataStorage/valuearray.hpp>

#include <boost/shared_ptr.hpp>
#include <boost/signals2.hpp>
#include <vector>

#include "image_state.hpp"
#include "image_properties.hpp"
#include "volume.hpp"
#include "types.hpp"
#include "util/common.hpp"

namespace isis
{
namespace glance
{
namespace data
{

class ImageBase
	: public ImageState,
  public ImageDataProperties,
  public ImageMetaProperties
{
public:
	typedef std::vector<Volume> VolumesType;

	enum ImageContentType { VOXELS, PROPERTIES_DATA, PROPERTIES_META, STATE, ALL };

	///Returns the underlying isis image.
	const isis::data::Image &get() const { return *isis_image_; }

	Volume &operator[]( VolumesType::size_type const &index ) {
		return volumes_[index];
	}
	const Volume &operator[]( VolumesType::size_type const &index ) const {
		return volumes_[index];
	}

	VolumesType::size_type size() const {
		return volumes_.size();
	}
protected:
	ImageBase( const isis::data::Image &image );

	/// @cond _internal
	API_EXCLUDE_BEGIN
	bool synchronizeMetaContentFrom( const isis::data::Image &image, const ImageContentType &content );
	API_EXCLUDE_END
	/// @endcond _internal

	const util::SharredPointer<isis::data::Image> isis_image_;

	VolumesType volumes_;
private:
	//do not allow to copy a glance::data::Image
	ImageBase( const ImageBase & );




};
} // end namespace data
} // end namespace glance
} // end namespace isis

#endif // _ISIS_GLANCE_IMAGE_BASE_HPP
