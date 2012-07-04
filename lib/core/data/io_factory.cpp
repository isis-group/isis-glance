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

namespace isis
{
namespace glance
{
namespace data
{

util::Signal<void ( const std::string & )> IOFactory::signal_start_loading_path;
util::Signal<void ( const std::string & )> IOFactory::signal_path_does_not_exist;
util::Signal<void ( const std::string & )> IOFactory::signal_failed_loading_from_path;
util::Signal<void ( const size_t &, const std::string & )> IOFactory::signal_loaded_n_images_from_path;

bool IOFactory::load ( ImageContainer &container, const isis::util::slist &paths,  const isis::util::istring &suffix_override, const isis::util::istring &dialect )
{
	return container.addImages( _load( paths, suffix_override, dialect ) );
}

ImageVector IOFactory::load ( const isis::util::slist &paths, const isis::util::istring &suffix_override, const isis::util::istring &dialect )
{
	return _load( paths, suffix_override, dialect );
}

ImageVector IOFactory::_load ( const isis::util::slist &paths, const isis::util::istring &suffix_override, const isis::util::istring &dialect )
{
	LoadingThreadListType loadingThreadList;
	ImageVector retVec;
	BOOST_FOREACH( const isis::util::slist::const_reference path, paths ) {
		const boost::filesystem::path p( path );

		if( !boost::filesystem::exists( p ) ) {
			signal_path_does_not_exist( path );
			LOG( Runtime, error ) << "Path " << path << " does not exist!.";
		} else {
			signal_start_loading_path( path );
			//we have to do this consecutively cause IOFactory uses Singletons and so is not thread-safe
			std::list<isis::data::Image> images = isis::data::IOFactory::load( path, suffix_override, dialect );

			if( images.size() == 0 ) {
				signal_failed_loading_from_path( path );
				//we do not need error messages here because isis will send them
			} else {
				signal_loaded_n_images_from_path( images.size(), path );
				boost::shared_ptr<_internal::LoadingThread> threadPtr;
				BOOST_FOREACH( std::list<isis::data::Image>::reference image, images ) {
					//setting the file_path so we can use that later
					image.setPropertyAs<std::string>( "file_path", path );
					threadPtr.reset( new _internal::LoadingThread( image ) );
					threadPtr->setDebugIdentification( path );
					threadPtr->start();
					loadingThreadList.push_back( threadPtr );
				}
			}
		}
	}
	//make sure all threads get the chance to finish
	BOOST_FOREACH( LoadingThreadListType::reference thread, loadingThreadList ) {
		thread->join();
	}
	BOOST_FOREACH( LoadingThreadListType::const_reference thread, loadingThreadList ) {
		if( thread->isRunning() ) {
			LOG( Runtime, error ) << "Trying to get image from thread " << thread->get().get_id()
								  << " but obviously this thread is still running.";
		} else {
			retVec.push_back( thread->viewerImage );
		}
	}
	return retVec;

}


} // end namespace data
} // end namespace glance
} // end namespace isis