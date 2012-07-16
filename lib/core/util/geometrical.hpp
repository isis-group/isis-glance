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
 * geometrical.hpp
 *
 * Description:
 *
 *  Created on: Jun 8, 2012
 *      Author: tuerke
 ******************************************************************/
#ifndef _ISIS_GLANCE_GEOMETRICAL_HPP
#define _ISIS_GLANCE_GEOMETRICAL_HPP

#include <CoreUtils/vector.hpp>
#include <CoreUtils/matrix.hpp>
#include <CoreUtils/propmap.hpp>

namespace isis
{
namespace glance
{
namespace util
{

template<unsigned short DIM>
isis::util::FixedVector<size_t, DIM> get32BitAlignedSize( const isis::util::FixedVector<size_t, DIM> &orig_size )
{
	isis::util::FixedVector<size_t, DIM> ret_size;

	for ( isis::util::ivector4::value_type i = 0; i < DIM; i++ ) {
		const int m = orig_size[i] % 4;

		if( m > 0 ) {
			ret_size[i] = orig_size[i] + 4 - m;
		} else {
			ret_size[i] = orig_size[i];
		}
	}

	return ret_size;
}

isis::util::Matrix3x3<float> getOrientationMatrixFromPropMap( const isis::util::PropertyMap &propmap );

isis::util::Matrix3x3<float> getLatchedOrienation( const isis::util::Matrix3x3<float> &orientation_matrix );


} // end namespace util
} // end namespace glance
} // end namespace isis

#endif // _ISIS_GLANCE_GEOMETRICAL_HPP