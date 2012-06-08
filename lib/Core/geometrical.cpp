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
 * geometrical.cpp
 *
 * Description:
 *
 *  Created on: Jun 8, 2012
 *      Author: tuerke
 ******************************************************************/
#include "geometrical.hpp"

namespace isis
{
namespace glance
{
namespace geometrical
{

util::ivector4 get32BitAlignedSize ( const util::ivector4 &orig_size )
{
	util::ivector4 ret_size;

	for ( util::ivector4::value_type i = 0; i < 4; i++ ) {
		const int m = orig_size[i] % 4;

		if( m > 0 ) {
			ret_size[i] = orig_size[i] + 4 - m;
		} else {
			ret_size[i] = orig_size[i];
		}
	}

	return ret_size;
}

isis::util::Matrix4x4< float > getOrientationMatrixFromPropMap ( const util::PropertyMap &propmap )
{
	const util::Matrix4x4<float> retMatrix (  propmap.getPropertyAs<util::fvector4>( "rowVec" ),
			propmap.getPropertyAs<util::fvector4>( "columnVec" ),
			propmap.getPropertyAs<util::fvector4>( "sliceVec" ) );
	return retMatrix.transpose(); // has to be transposed!!!!!!!!!!
}

isis::util::Matrix4x4< float > getLatchedOrienation ( const isis::util::Matrix4x4< float > &orientation_matrix )
{
	util::Matrix4x4<float> retMatrix;
	retMatrix.fill( 0 );
	const util::fvector4 &rowVec = orientation_matrix.getRow( 0 );
	const util::fvector4 &columnVec = orientation_matrix.getRow( 1 );
	const util::fvector4 &sliceVec = orientation_matrix.getRow( 2 );

	size_t rB = rowVec.getBiggestVecElemAbs();
	size_t cB = columnVec.getBiggestVecElemAbs();
	size_t sB = sliceVec.getBiggestVecElemAbs();

	if( rB == cB ) {
		if( sB == 0 ) {
			rB = 1;
			cB = 2;
		} else if ( sB == 1 ) {
			rB = 2;
			cB = 0;
		} else if ( sB == 2 ) {
			rB = 0;
			cB = 1;
		}
	}

	if( rB == sB ) {
		if( cB == 0 ) {
			rB = 2;
			sB = 1;
		} else if ( cB == 1 ) {
			rB = 2;
			sB = 0;
		} else if ( cB == 2 ) {
			rB = 1;
			sB = 0;
		}
	}

	if( cB == sB ) {
		if( rB == 0 ) {
			cB = 1;
			sB = 2;
		} else if ( rB == 1 ) {
			cB = 2;
			sB = 0;
		} else if ( rB == 2 ) {
			cB = 1;
			sB = 0;
		}
	}

	retMatrix.elem( 0, rB ) = rowVec[rB] < 0 ? -1 : 1;
	retMatrix.elem( 1, cB ) =  columnVec[cB] < 0 ? -1 : 1;
	retMatrix.elem( 2, sB ) = sliceVec[sB] < 0 ? -1 : 1;
	retMatrix.elem( 3, 3 ) = 1;
	return retMatrix;
}



} // end namespace geometrical
} // end namespace glance
} // end namespace isis