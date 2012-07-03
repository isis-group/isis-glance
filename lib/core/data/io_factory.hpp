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

namespace _internal
{
class LoadingThread : public isis::glance::util::Thread
{
public:
	LoadingThread( const isis::data::Image &image  );
	void operator() ();

	ImageSharedPointer viewerImage;
private:

	isis::data::Image image_;
	ImageVector images_;

};
}


class IOFactory
{
	typedef std::list<boost::shared_ptr<_internal::LoadingThread> > LoadingThreadListType;
public:


	static bool load( ImageContainer &container, const isis::util::slist &paths, const isis::util::istring &suffix_override = "", const isis::util::istring &dialect = "" );

	static ImageVector load( const isis::util::slist &paths, const isis::util::istring &suffix_override = "", const isis::util::istring &dialect = "" );

	//signals
	static util::Signal<void ( const std::string & )> signal_start_loading_path;
	static util::Signal<void ( const std::string & )> signal_path_does_not_exist;
	static util::Signal<void ( const std::string & )> signal_failed_loading_from_path;
	static util::Signal<void ( const size_t &, const std::string & )> signal_loaded_n_images_from_path;
private:
	static ImageVector _load(  const isis::util::slist &paths, const isis::util::istring &suffix_override = "", const isis::util::istring &dialect = "" );

};

} // end namespace data
} // end namespace glance
} // end namespace isis


#endif // _ISIS_GLANCE_IO_FACTORY_HPP