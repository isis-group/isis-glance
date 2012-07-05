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
 * volume.cpp
 *
 * Description:
 *
 *  Created on: Jul 5, 2012
 *      Author: tuerke
 ******************************************************************/
#include "volume.hpp"
#include <cstring>

namespace isis
{
namespace glance
{
namespace data
{

Volume::Volume ( const isis::data::ValueArrayReference &src, const size_t dims[] )
	: DataContainer< 3 > ( src, dims )
{}

Slice Volume::extractSlice ( const fvec &perpendicular, const ivec &coords ) const
{
	const isis::data::ValueArrayBase *src = this->operator->();
	const size_t bytesPerElem = src->bytesPerElem();
	const uint8_t *srcPtr = static_cast<const uint8_t *>( src->getRawAddress().get() );
	const size_type size = getSizeAsVector();
	Slice::size_type size2d;

	//we can define some special cases to increase performance
	if( std::abs( perpendicular[2] ) == 1 ) {
		const isis::data::ValueArrayReference dest = src->cloneToNew( size[0] * size[1] );
		uint8_t *destPtr = static_cast<uint8_t *>( dest->getRawAddress().get() );
		std::memcpy( destPtr,
					 srcPtr + size[0] * size[1] * coords[2],
					 size[0] * size[1] * bytesPerElem );
		size2d[0] = size[0];
		size2d[1] = size[1];
		return Slice( dest, size2d );
	} else if ( std::abs( perpendicular[1] ) == 1 ) {
		const isis::data::ValueArrayReference dest = src->cloneToNew( size[0] * size[2] );
		uint8_t *destPtr = static_cast<uint8_t *>( dest->getRawAddress().get() );

		for( size_t slice = 0; slice < size[2]; slice++ ) {
			std::memcpy( destPtr + size[0] * slice,
						 srcPtr + size[0] * coords[1] + size[0] * size[1] * slice,
						 size[0] * bytesPerElem );
		}

		size2d[0] = size[0];
		size2d[1] = size[2];
		return Slice( dest, size2d );
	} else if ( std::abs( perpendicular[0] ) == 1 ) {
		const isis::data::ValueArrayReference dest = src->cloneToNew( size[1] * size[2] );
		uint8_t *destPtr = static_cast<uint8_t *>( dest->getRawAddress().get() );

		for( size_t slice = 0; slice < size[2]; slice++ ) {
			for( size_t column = 0; column < size[1]; column++ ) {
				destPtr[column + size[1] * slice] = srcPtr[coords[0] + column * size[0] + slice * size[0] * size[1]];
			}
		}

		size2d[0] = size[1];
		size2d[1] = size[2];
		return Slice( dest, size2d );
	}
}


} // end namespace data
} // end namespace glance
} // end namespace isis
