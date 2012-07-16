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
 * volume.hpp
 *
 * Description:
 *
 *  Created on: Jul 5, 2012
 *      Author: tuerke
 ******************************************************************/
#ifndef _ISIS_GLANCE_VOLUME_HPP
#define _ISIS_GLANCE_VOLUME_HPP

#include <boost/shared_array.hpp>

#include "data_container.hpp"
#include "common.hpp"
#include "slice.hpp"
#include "data_handler.hpp"
#include "util/geometrical.hpp"

namespace isis
{
namespace glance
{
namespace data
{
class Volume : public _internal::DataContainer<3>
{
public:
	typedef isis::util::vector3<size_t> size_type;
	typedef isis::util::fvector3 fvec;
	typedef isis::util::ivector4 ivec;
	typedef isis::util::dvector3 dvec;
	
	Volume ( const isis::data::ValueArrayReference &src, const size_type &size );
	Volume ( const isis::data::ValueArrayReference &src, const size_type &size, const ImageSharedPointer parentImage );

	Slice extractSlice( fvec perpendicular, const ivec &coords, bool force32BitAligned = false ) const;
	std::vector< isis::glance::data::Slice > extractAllSlices ( fvec perpendicular, bool force32BitAligned = false ) const;

	const ImageSharedPointer getParent() const { return parentImage_; }

	DataHandler::permutation_type getPermutationSagittal( bool aligned32Bit ) const;

	inline size_type getSize( bool aligned32Bit ) const {
		if( aligned32Bit ) {
			return isis::glance::util::get32BitAlignedSize<3>( getSizeAsVector() );
		} else {
			return getSizeAsVector();
		}
	};


private:
	Slice extractSliceGeneric( const fvec &perpendicular, const ivec &coords, bool force32BitAligned ) const;

	Slice extractSliceAxial( const isis::data::ValueArrayBase *src, const size_t &slice, const size_type &size, const size_type &sliceSize, const size_t &bytesPerElem, const size_t &typeFac ) const;
	Slice extractSliceCoronal( const isis::data::ValueArrayBase *src, const size_t &slice, const size_type &size, const size_type &sliceSize, const size_t &bytesPerElem, const size_t &typeFac ) const;

	ImageSharedPointer parentImage_;
	DataHandler::permutation_type permutationSagittal_;
	DataHandler::permutation_type permutationSagittalAligned32Bit_;

};
} // end namespace data
} // end namespace glance
} // end namespace isis

#endif // _ISIS_GLANCE_VOLUME_HPP