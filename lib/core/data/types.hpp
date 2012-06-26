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
 * types.hpp
 *
 * Description:
 *
 *  Created on: Jun 26, 2012
 *      Author: tuerke
 ******************************************************************/
#ifndef _ISIS_GLANCE_DATA_TYPES_HPP
#define _ISIS_GLANCE_DATA_TYPES_HPP

#include <CoreUtils/vector.hpp>
#include <CoreUtils/color.hpp>
#include <DataStorage/valuearray.hpp>
#include <complex>

namespace isis
{
namespace glance
{
namespace data
{
namespace types {

typedef uint8_t ScalarRepnProposed;
typedef util::color24 ColorRepnProposed;
typedef util::fvector4 VectorRepnProposed;
typedef std::complex< float > ComplexRepnProposed;

enum ImageDataType {UNDEFINED = 0,
					FLOAT = isis::data::ValueArray<float>::staticID,
					DOUBLE = isis::data::ValueArray<double>::staticID,
					UINT8_T = isis::data::ValueArray<uint8_t>::staticID,
					INT8_T = isis::data::ValueArray<int8_t>::staticID,
					UINT16_T = isis::data::ValueArray<uint16_t>::staticID,
					INT16_T = isis::data::ValueArray<int16_t>::staticID,
					UINT32_T = isis::data::ValueArray<uint32_t>::staticID,
					INT32_T = isis::data::ValueArray<int32_t>::staticID,
					UINT64_T = isis::data::ValueArray<uint64_t>::staticID,
					INT64_T = isis::data::ValueArray<int64_t>::staticID,
					BOOL = isis::data::ValueArray<bool>::staticID,
					COLOR_24 = isis::data::ValueArray<isis::util::color24>::staticID,
					COLOR_48 = isis::data::ValueArray<isis::util::color48>::staticID,
					COMPLEX_FLOAT = isis::data::ValueArray<std::complex<float> >::staticID,
					COMPLEX_DOUBLE = isis::data::ValueArray<std::complex<double> >::staticID,
					VECTOR4_FLOAT = isis::data::ValueArray< isis::util::fvector4 >::staticID,
					VECTOR4_DOUBLE = isis::data::ValueArray< isis::util::dvector4 >::staticID,
					VECTOR4_INT = isis::data::ValueArray< isis::util::ivector4 >::staticID,
					SCALAR_PROPOSED = isis::data::ValueArray< ScalarRepnProposed >::staticID,
					COLOR_PROPOSED = isis::data::ValueArray< ColorRepnProposed >::staticID,
					VECTOR_PROPOSED = isis::data::ValueArray< VectorRepnProposed >::staticID,
					COMPLEX_PROPOSED = isis::data::ValueArray< ComplexRepnProposed >::staticID,
				   };
} // end namespace types
} // end namespace data
} // end namespace glance
} // end namespace isis

#endif // _ISIS_GLANCE_DATA_TYPES_HPP