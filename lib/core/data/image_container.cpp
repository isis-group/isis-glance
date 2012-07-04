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
 * image_container.cpp
 *
 * Description:
 *
 *  Created on: Jun 8, 2012
 *      Author: tuerke
 ******************************************************************/
#include "image_container.hpp"

namespace isis
{
namespace glance
{
namespace data
{

ImageContainer::ImageContainer()
	: allow_multiple_( false )
{}

bool ImageContainer::addImage ( const ImageSharedPointer &image )
{
	if ( !hasImage( image ) || allow_multiple_ ) {
		push_back( image );
		signal_image_added( *this, image );
		return true;
	} else {
		LOG( data::Runtime, warning ) << "Trying to add already existing image with file_path: "
									  << image->file_path << " ! Will not do that.";
		return false;
	}
}

bool ImageContainer::addImages ( const ImageVector &images )
{
	bool ok = true;
	BOOST_FOREACH( const ImageVector::const_reference image, images ) {
		ok = ok && addImage( image );
	}
	return ok;
}

bool ImageContainer::removeImage ( const ImageSharedPointer &image )
{
	iterator iter = std::find( begin(), end(), image );

	if( iter == end() ) {
		return false;
	} else {
		erase( iter );
		signal_image_removed( *this, image );
		return true;
	}
}

bool ImageContainer::hasImage ( const isis::glance::data::ImageSharedPointer &image ) const
{
	return std::find( begin(), end(), image ) != end();
}


} // end namespace data
} // end namespace glance
} // end namespace isis