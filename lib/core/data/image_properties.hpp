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

#include "types.hpp"

namespace isis
{
namespace glance
{
namespace data
{
/**
 * ImageProperties combines all the properties of an
 * image that need to provide fast access for read and write accress.
 */

class ImageMetaProperties
{
public:
	typedef isis::util::FixedVector<size_t, 4> SizeType;
	typedef isis::util::Matrix4x4<float> OrientationMatrixType;

	/**
	 * Empty constructur for ImageProperties
	 */
	ImageMetaProperties(){};

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
	ImageMetaProperties( const isis::data::Image &image );

	///The images filename
	std::string file_name;

	///The images filepath
	std::string file_path;

	///The images size
	SizeType image_size;

	///The images size aligned to 32bit
	SizeType image_size_aligned32;

	///The image orientation matrix
	OrientationMatrixType orientation_matrix;

	///The latched orientation_matrix
	OrientationMatrixType orientation_matrix_latched;

	///The sum of voxelSize and voxelGap
	util::fvector4 voxel_size;


	util::PropertyMap getAdditionalProperties() const { return additional_properties_; }
	
protected:
	const bool &isValid() const { return is_valid_; }

private:
	bool is_valid_;
	isis::util::PropertyMap additional_properties_;


};

class ImageDataProperties {
public:
	/**
	 * Groups of types an image can have
	 */
	enum ImageTypeGroup { SCALAR, COMPLEX, COLOR, VECTOR };

	ImageDataProperties( const isis::data::Image &image );

	ImageDataProperties() {}
	
	///The minimum/maximum as double
	std::pair<double, double> min_max;

	///The extent of the images min <> max
	double extent;

	///The major type ID of the image
	ImageDataType major_type;

	///Does the underlying isis image contains of chunks with only one image type?
	bool has_one_type;

	///The images type group
	ImageTypeGroup type_group;
private:
	ImageDataType getMajorType( const std::pair<util::ValueReference, util::ValueReference> &_min_max ) const;
	bool getHasOneType( const isis::data::Image &image ) const;
};

} // end namespace data
} // end namespace glance
} // end namespace isis


#endif // _ISIS_GLANCE_IMAGE_PROPERTIES_HPP