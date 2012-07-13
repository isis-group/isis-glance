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
 * data_handler.cpp
 *
 * Description:
 *
 *  Created on: Jul 12, 2012
 *      Author: tuerke
 ******************************************************************/
#include "data_handler.hpp"
#include "volume.hpp"
#include "image.hpp"

namespace isis
{
namespace glance
{
namespace data
{
#ifdef ISIS_GLANCE_USE_LIBOIL
	
namespace _internal
{

#define IMPL_OIL_EXTRACT_SAG( TYPE, OIL_SUFFIX ) \
	template<> void oilExtractSagittal<TYPE>( TYPE *destPtr, const TYPE *srcPtr, const int32_t *permutation, const size_t &length ) {\
		oil_permute_ ## OIL_SUFFIX ( destPtr, sizeof(TYPE), srcPtr, sizeof(TYPE), permutation, 4, length ); \
}

IMPL_OIL_EXTRACT_SAG( int8_t, s8 )
IMPL_OIL_EXTRACT_SAG( uint8_t, u8 )

IMPL_OIL_EXTRACT_SAG( int16_t, s16 )
IMPL_OIL_EXTRACT_SAG( uint16_t, u16 )

IMPL_OIL_EXTRACT_SAG( int32_t, s32 )
IMPL_OIL_EXTRACT_SAG( uint32_t, u32 )

IMPL_OIL_EXTRACT_SAG( double, f64 )
IMPL_OIL_EXTRACT_SAG( float, f32 )

}

#endif

Slice DataHandler::extractSagittal ( const Volume &vol, const int32_t &x )
{
#ifdef ISIS_GLANCE_USE_LIBOIL
	const static _internal::OilInitializer initializeOil;
#endif

	switch( vol->getTypeID() ) {
	case isis::data::ValueArray<int8_t>::staticID:
		return _extractSagittal<int8_t>( *vol.operator->(), vol.getSizeAsVector()[1], vol.getSizeAsVector()[2], x, vol.getPermutationSagittal() );
	case isis::data::ValueArray<uint8_t>::staticID:
		return _extractSagittal<uint8_t>( *vol.operator->(), vol.getSizeAsVector()[1], vol.getSizeAsVector()[2], x, vol.getPermutationSagittal() );
	case isis::data::ValueArray<int16_t>::staticID:
		return _extractSagittal<int16_t>( *vol.operator->(), vol.getSizeAsVector()[1], vol.getSizeAsVector()[2], x, vol.getPermutationSagittal() );
	case isis::data::ValueArray<uint16_t>::staticID:
		return _extractSagittal<uint16_t>( *vol.operator->(), vol.getSizeAsVector()[1], vol.getSizeAsVector()[2], x, vol.getPermutationSagittal() );
	case isis::data::ValueArray<int32_t>::staticID:
		return _extractSagittal<int32_t>( *vol.operator->(), vol.getSizeAsVector()[1], vol.getSizeAsVector()[2], x, vol.getPermutationSagittal() );
	case isis::data::ValueArray<uint32_t>::staticID:
		return _extractSagittal<uint32_t>( *vol.operator->(), vol.getSizeAsVector()[1], vol.getSizeAsVector()[2], x, vol.getPermutationSagittal() );
	case isis::data::ValueArray<int64_t>::staticID:
		return _extractSagittal<int64_t>( *vol.operator->(), vol.getSizeAsVector()[1], vol.getSizeAsVector()[2], x, vol.getPermutationSagittal() );
	case isis::data::ValueArray<uint64_t>::staticID:
		return _extractSagittal<uint64_t>( *vol.operator->(), vol.getSizeAsVector()[1], vol.getSizeAsVector()[2], x, vol.getPermutationSagittal() );
	case isis::data::ValueArray<float>::staticID:
		return _extractSagittal<float>( *vol.operator->(), vol.getSizeAsVector()[1], vol.getSizeAsVector()[2], x, vol.getPermutationSagittal() );
	case isis::data::ValueArray<double>::staticID:
		return _extractSagittal<double>( *vol.operator->(), vol.getSizeAsVector()[1], vol.getSizeAsVector()[2], x, vol.getPermutationSagittal() );
	case isis::data::ValueArray<isis::util::color24>::staticID:
		return _extractSagittal<isis::util::color24>( *vol.operator->(), vol.getSizeAsVector()[1], vol.getSizeAsVector()[2], x, vol.getPermutationSagittal() );
	case isis::data::ValueArray<isis::util::color48>::staticID:
		return _extractSagittal<isis::util::color48>( *vol.operator->(), vol.getSizeAsVector()[1], vol.getSizeAsVector()[2], x, vol.getPermutationSagittal() );
	case isis::data::ValueArray<std::complex<float> >::staticID:
		return _extractSagittal<std::complex<float> >( *vol.operator->(), vol.getSizeAsVector()[1], vol.getSizeAsVector()[2], x, vol.getPermutationSagittal() );
	case isis::data::ValueArray<std::complex<double> >::staticID:
		return _extractSagittal<std::complex<double> >( *vol.operator->(), vol.getSizeAsVector()[1], vol.getSizeAsVector()[2], x, vol.getPermutationSagittal() );
	default:
		LOG( Runtime, error ) << "Extraction of sagittal slice is not yet implemented for type " << isis::util::getTypeMap(false).at(vol->getTypeID() );
	}

}

DataHandler::PermutationType DataHandler::getPermutationSagittal ( const Volume::size_type &size )
{
	boost::shared_array<int32_t> retPerm( new int32_t[size[1]*size[2]] );
	size_t index = 0;

	for( size_t z = 0; z < size[2]; z++ ) {
		for( size_t y = 0; y < size[1]; y++ ) {
			retPerm[index++] = y * size[0] + z * size[0] * size[1];
		}
	}

	return retPerm;
}



} // end namespace data
} // end namespace glance
} // end namespace isis