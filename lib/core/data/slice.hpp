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
 * slice.hpp
 *
 * Description:
 *
 *  Created on: Jul 5, 2012
 *      Author: tuerke
 ******************************************************************/
#ifndef _ISIS_GLANCE_SLICE_HPP
#define _ISIS_GLANCE_SLICE_HPP

#include "data_container.hpp"
#include <CoreUtils/vector.hpp>

namespace isis
{
namespace glance
{
namespace data
{
namespace _internal
{
template<typename TYPE>
class vector2 : public isis::util::FixedVector<TYPE,2>
{
public:
	vector2() {}
	vector2( const TYPE src[2] ): isis::util::FixedVector< TYPE, 2>( src ) {}
	vector2( TYPE first, TYPE second ) {
		this->operator[]( 1 ) = second;
		this->operator[]( 0 ) = first;
	}
};
}
	
class Slice : public _internal::DataContainer<2>
{
public:
	typedef _internal::vector2<float> fvec;
	typedef _internal::vector2<int32_t> ivec;
	typedef _internal::vector2<double> dvec;
	typedef _internal::vector2<size_t> size_type;
	
	Slice ( const isis::data::ValueArrayReference &src,  const size_t dims[] )
		: DataContainer< 2 >( src, dims ) {};
	Slice ( const isis::data::ValueArrayReference &src, const size_type &dims )
		: DataContainer< 2 >( src, dims ) {}
};

} // end namespace data
} // end namespace glance
} // end namespace isis


#endif // _ISIS_GLANCE_SLICE_HPP