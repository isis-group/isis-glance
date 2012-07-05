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
 * container.hpp
 *
 * Description:
 *
 *  Created on: Jun 25, 2012
 *      Author: tuerke
 ******************************************************************/
#ifndef _ISIS_GLANCE_DATA_CONTAINER_HPP
#define _ISIS_GLANCE_DATA_CONTAINER_HPP

#include <DataStorage/ndimensional.hpp>
#include <DataStorage/valuearray.hpp>

namespace isis
{
namespace glance
{
namespace data
{
namespace _internal
{

template<unsigned short DIMS>
class DataContainer
	: public isis::data::_internal::NDimensional<DIMS>,
  public isis::data::ValueArrayReference
{
public:
	typedef isis::util::FixedVector<float, DIMS> fvec;
	typedef isis::util::FixedVector<int32_t, DIMS> ivec;
	typedef isis::util::FixedVector<double, DIMS> dvec;
	typedef isis::util::FixedVector<size_t, DIMS> size_type;

	inline DataContainer( const isis::data::ValueArrayReference &src, const size_t dims[DIMS] )
		: isis::data::ValueArrayReference( src ) {
		isis::data::_internal::NDimensional<DIMS>::init( dims );
	}

	inline DataContainer( const isis::data::ValueArrayReference &src, const size_type &dims )
		: isis::data::ValueArrayReference( src ) {
		size_t size_[DIMS];

		for( size_t d = 0; d < DIMS; d++ ) {
			size_[d] = dims[d];
		}

		isis::data::_internal::NDimensional<DIMS>::init( size_ );
	}


	template<typename TYPE>
	inline TYPE &voxel( const size_t dims[DIMS] ) {
		assert( ( *this )->getTypeID() == isis::data::ValueArray<TYPE>::staticID );
		//hopefully the user knows what he is doing in release build
		isis::data::ValueArrayBase &me = **this;
		isis::data::ValueArray<TYPE> &ret = me.castToValueArray<TYPE>();
		return ret[isis::data::_internal::NDimensional<DIMS>::getLinearIndex( dims )];
	}

	template<typename TYPE>
	inline const TYPE &voxel( const size_t dims[DIMS] )const {
		assert( ( *this )->getTypeID() == isis::data::ValueArray<TYPE>::staticID );
		//hopefully the user knows what he is doing in release build
		const isis::data::ValueArrayBase &me = **this;
		const isis::data::ValueArray<TYPE> &ret = me.castToValueArray<TYPE>();
		return ret[isis::data::_internal::NDimensional<DIMS>::getLinearIndex( dims )];
	}
};

} // end namespace _internal
} // end namespace data
} // end namespace glance
} // end namespace isis

#endif // _ISIS_GLANCE_DATA_CONTAINER_HPP