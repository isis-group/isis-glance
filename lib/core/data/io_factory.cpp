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
 * io_factory.cpp
 *
 * Description:
 *
 *  Created on: Jul 2, 2012
 *      Author: tuerke
 ******************************************************************/
#include "io_factory.hpp"

namespace isis {
namespace glance {
namespace data {
namespace _internal {

LoadingThread::LoadingThread ( const isis::data::Image &image )
	: image_( image )
{}


void LoadingThread::operator() ()
{
	LOG( Debug, verbose_info ) << "Starting loading thread " << get().get_id();
	viewerImage.reset( new Image( image_ ) );
	LOG( Debug, verbose_info ) << "Finished loading thread " << get().get_id();
}


}
util::Signal<void ( const std::string &)> IOFactory::signal_start_loading_path;
util::Signal<void ( const std::string &)> IOFactory::signal_path_does_not_exist;
util::Signal<void ( const std::string &)> IOFactory::signal_failed_loading_from_path;
util::Signal<void ( const size_t &, const std::string &)> IOFactory::signal_loaded_n_images_from_path;

bool IOFactory::load ( ImageContainer &container, const isis::util::slist& paths,  const isis::util::istring& suffix_override, const isis::util::istring& dialect )
{
	return container.addImages( _load( paths, suffix_override, dialect ) );
}

ImageVector IOFactory::load ( const isis::util::slist& paths, const isis::util::istring& suffix_override, const isis::util::istring& dialect )
{
	return _load( paths, suffix_override, dialect );
}

ImageVector IOFactory::_load ( const isis::util::slist& paths, const isis::util::istring& suffix_override, const isis::util::istring& dialect )
{
	LoadingThreadListType loadingThreadList;
	ImageVector retVec;
	BOOST_FOREACH( const isis::util::slist::const_reference path, paths ) {
		const boost::filesystem::path p( path );
		if( !boost::filesystem::exists( p ) ) {
			signal_path_does_not_exist.call(path);
			LOG( Runtime, error ) << "Path " << path << " does not exist!.";
		} else {
			const std::list<isis::data::Image> images = isis::data::IOFactory::load( path, suffix_override, dialect );
			if( images.size() == 0 ) {
				signal_failed_loading_from_path.call(path);
				//we do not need error messages here because isis will send them
			} else {
				signal_loaded_n_images_from_path.call( images.size(), path );
				boost::shared_ptr<_internal::LoadingThread> threadPtr;
				BOOST_FOREACH( std::list<isis::data::Image>::const_reference image, images ) {
					threadPtr.reset(new _internal::LoadingThread( image ) );
					threadPtr->setDebugIdentification(path);
					loadingThreadList.push_back( threadPtr );
					loadingThreadList.back()->start();
				}
			}
		}
	}
	BOOST_FOREACH( LoadingThreadListType::reference thread, loadingThreadList ) {
		thread->join();
	}
	BOOST_FOREACH( LoadingThreadListType::const_reference thread, loadingThreadList ) {
		retVec.push_back( thread->viewerImage );
	}
	return retVec;
	
}


} // end namespace data
} // end namespace glance
} // end namespace isis