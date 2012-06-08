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
 * image_properties.hpp
 *
 * Description:
 *
 *  Created on: Jun 8, 2012
 *      Author: tuerke
 ******************************************************************/

#ifndef _ISIS_GLANCE_IMAGE_PROPERTIES_HPP
#define _ISIS_GLANCE_IMAGE_PROPERTIES_HPP

#include <string>
#include <CoreUtils/vector.hpp>
#include <CoreUtils/matrix.hpp>
#include <DataStorage/image.hpp>

namespace isis
{
namespace glance
{

/**
 * ImageProperties combines all the properties of an
 * image that need to have fast access to read and write.
 */

class ImageProperties
{
public:
	ImageProperties();

	/**
	 * Constructs an ImageProperties object with an isis::data::Image object
	 *
	 * ImageProperties expects the \param image to have the following properties set:
	 *
	 * * "file_path"
	 *
	 * If ImageProperties could not find one of these properties it throws a warning
	 * and "isValid" will return false.
	 *
	 */

	ImageProperties( const isis::data::Image &image );

	///The images filename
	std::string file_name;

	///The images filepath
	std::string file_path;

	///The minimum/maximum as double
	std::pair<double, double> min_max;

	///The extent of the images min <> max
	double extent;

	///The major type ID of the image
	unsigned int major_type_id;

	///The images size
	util::ivector4 size;

	///The images size aligned to 32bit
	util::ivector4 size_aligned32;

	///Do we have a RGB image?
	bool is_rgb;

	///The image orientation matrix
	util::Matrix4x4<float> orientation_matrix;

	///The latched orientation_matrix
	util::Matrix4x4<float> orientation_matrix_latched;

protected:
	const bool &isValid() const { return is_valid_; }

private:
	short unsigned int getMajorTypeID( const std::pair<util::ValueReference, util::ValueReference> &_min_max ) const;
	bool is_valid_;


};

} // end namespace glance
} // end namespace isis


#endif // _ISIS_GLANCE_IMAGE_PROPERTIES_HPP