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
 * data_handler.hpp
 *
 * Description:
 *
 *  Created on: Jul 12, 2012
 *      Author: tuerke
 ******************************************************************/
#ifndef _ISIS_GLANCE_DATA_HANDLER_HPP
#define _ISIS_GLANCE_DATA_HANDLER_HPP

#include <boost/shared_array.hpp>
#include <map>
#include <CoreUtils/vector.hpp>
#include <DataStorage/valuearray_base.hpp>
#include "slice.hpp"


#ifdef ISIS_GLANCE_USE_LIBOIL
extern "C" {
#include <liboil/liboil.h>
}
#endif

namespace isis {
namespace glance {
namespace data {

namespace _internal {
struct OilInitializer {
	OilInitializer() {
#ifdef ISIS_GLANCE_USE_LIBOIL
		oil_init();
#endif // ISIS_USE_LIBOIL
	}
};

#ifdef ISIS_GLANCE_USE_LIBOIL
template<typename T>
void _oilExtractSagittal( T* destPtr, const T* srcPtr, const int32_t* permutation, const size_t &length )
{
	for ( size_t index = 0; index < length; index++ ) {
			destPtr[index] = srcPtr[permutation[index]];
	}
}

template<>
void _oilExtractSagittal<uint8_t>( uint8_t* destPtr, const uint8_t* srcPtr, const int32_t* permutation, const size_t &length );

template<>
void _oilExtractSagittal<int8_t>( int8_t* destPtr, const int8_t* srcPtr, const int32_t* permutation, const size_t &length );

template<>
void _oilExtractSagittal<float>( float* destPtr, const float* srcPtr, const int32_t* permutation, const size_t &length );

template<>
void _oilExtractSagittal<double>( double* destPtr, const double* srcPtr, const int32_t* permutation, const size_t &length );

template<>
void _oilExtractSagittal<int16_t>( int16_t* destPtr, const int16_t* srcPtr, const int32_t* permutation, const size_t &length );

template<>
void _oilExtractSagittal<uint16_t>( uint16_t* destPtr, const uint16_t* srcPtr, const int32_t* permutation, const size_t &length );

template<>
void _oilExtractSagittal<int32_t>( int32_t* destPtr, const int32_t* srcPtr, const int32_t* permutation, const size_t &length );

template<>
void _oilExtractSagittal<uint32_t>( uint32_t* destPtr, const uint32_t* srcPtr, const int32_t* permutation, const size_t &length );


#endif
}

class Volume;
class DataHandler
{
public:
	typedef boost::shared_array<int32_t> PermutationType;

	static Slice extractSagittal( const Volume &vol, const int32_t &x );

	static PermutationType getPermutationSagittal( const isis::util::FixedVector<size_t,3> &size );
private:
	template<typename T>
	static Slice _extractSagittal( const isis::data::ValueArrayBase &src, const size_t &col, const size_t &slice, const size_t &offset, DataHandler::PermutationType permutation ) {
		const T* srcPtr = static_cast<const T *>( src.getRawAddress(offset).get() );
		const isis::data::ValueArrayReference dest = src.cloneToNew( col * slice );
		T *destPtr = static_cast<T *>( dest->getRawAddress().get() );
#ifdef ISIS_GLANCE_USE_LIBOIL
		_internal::_oilExtractSagittal<T>( destPtr, srcPtr, permutation.get(), col * slice );
#else 
		for ( size_t index = 0; index < (col*slice); index++ ) {
			destPtr[index] = srcPtr[permutation[index]];
		}
#endif
		return Slice( dest, Slice::size_type( col, slice ) );
	}
};


	

} // end namespace data
} // end namespace glance
} // end namespace isis

#endif // _ISIS_GLANCE_DATA_HANDLER_HPP