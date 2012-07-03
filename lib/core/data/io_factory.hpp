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
 * io_factory.hpp
 *
 * Description:
 *
 *  Created on: Jul 2, 2012
 *      Author: tuerke
 ******************************************************************/
#ifndef _ISIS_GLANCE_IO_FACTORY_HPP
#define _ISIS_GLANCE_IO_FACTORY_HPP

#include "image_container.hpp"
#include "util/thread.hpp"
// #include "util/signals.hpp"

#include <DataStorage/io_factory.hpp>

#include <boost/filesystem.hpp>
#include <boost/signals2.hpp>

namespace isis
{
namespace glance
{
namespace data
{
/// @cond _internal
API_EXCLUDE_BEGIN
namespace _internal
{
class LoadingThread : public isis::glance::util::Thread
{
public:
	LoadingThread( const isis::data::Image &image  ) : image_( image ) {};
	void run()	{
		LOG( Debug, verbose_info ) << "Start loading thread " << get().get_id();
		viewerImage.reset( new Image( image_ ) );
		LOG( Debug, verbose_info ) << "Finished loading thread " << get().get_id();
	};
	
	ImageSharedPointer viewerImage;
private:
	isis::data::Image image_;
	ImageVector images_;

};
}
API_EXCLUDE_END
/// @endcond _internal

class IOFactory
{
	typedef std::list<boost::shared_ptr<_internal::LoadingThread> > LoadingThreadListType;
public:

	/**
	 *	Load images from a list of paths and pass them to the image container.
	 * \param container The container where the images should be passed to.
	 * \param paths A list of paths where the images should be loaded from. Is handed to the isis::data::IOFactory::load function.
	 * \param suffix_override This parameter is handed to the isis::data::IOFactory::load function.
	 * \param dialect This parameter is handed to the isis::data::IOFactory::load function.
	 * \return True if passing images to container was successful. Otherwise false.
	 */
	static bool load( ImageContainer &container, const isis::util::slist &paths, const isis::util::istring &suffix_override = "", const isis::util::istring &dialect = "" );

	/**
	 *	Load and return a list of images from a list of paths.
	 * \param paths A list of paths where the images should be loaded from. Is handed to the isis::data::IOFactory::load function.
	 * \param suffix_override This parameter is handed to the isis::data::IOFactory::load function.
	 * \param dialect This parameter is handed to the isis::data::IOFactory::load function.
	 */
	static ImageVector load( const isis::util::slist &paths, const isis::util::istring &suffix_override = "", const isis::util::istring &dialect = "" );

	//signals
	///This signal is called when starting to load a path
	static util::Signal<void ( const std::string & )> signal_start_loading_path;
	///This signal is called if a certain path does not exist
	static util::Signal<void ( const std::string & )> signal_path_does_not_exist;
	///This signal is called if a path could not be loaded
	static util::Signal<void ( const std::string & )> signal_failed_loading_from_path;
	///This signal is called when n>0 images are loaded from path
	static util::Signal<void ( const size_t &, const std::string & )> signal_loaded_n_images_from_path;
	///This signal is called when loading the paths and creating the isis::glance::data::Image (s) is finished
	static util::Signal<void ()> signal_finished_loading;
private:
	/// @cond _internal
	API_EXCLUDE_BEGIN
	static ImageVector _load(  const isis::util::slist &paths, const isis::util::istring &suffix_override = "", const isis::util::istring &dialect = "" );
	API_EXCLUDE_END
	/// @endcond _internal
};

} // end namespace data
} // end namespace glance
} // end namespace isis


#endif // _ISIS_GLANCE_IO_FACTORY_HPP