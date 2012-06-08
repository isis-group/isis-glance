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

namespace isis {
namespace glance {
namespace geometrical {

util::ivector4 get32BitAlignedSize ( const util::ivector4& orig_size )
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

	
} // end namespace geometrical
} // end namespace glance
} // end namespace isis