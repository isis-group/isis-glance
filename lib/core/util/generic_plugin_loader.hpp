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
 * generic_plugin_loader.hpp
 *
 * Description:
 *
 *  Created on: Jul 4, 2012
 *      Author: tuerke
 ******************************************************************/
#ifndef _ISIS_GLANCE_GENERIC_PLUGIN_LOADER_HPP
#define _ISIS_GLANCE_GENERIC_PLUGIN_LOADER_HPP

#include <stdlib.h>
#include <boost/shared_ptr.hpp>
#include <boost/filesystem.hpp>

#include <CoreUtils/singletons.hpp>
#include <CoreUtils/types.hpp>
#include <CoreUtils/propmap.hpp>

#include "common.hpp"
#include "signal.hpp"

#include <dlfcn.h>

namespace isis
{
namespace glance
{
namespace util
{
namespace _internal
{

template<typename Interface>
class PluginDeleterBase
{
public:
	void setHandle( void *handle ) { dlHandle_ = handle; }
	void setPluginName( std::string pluginName ) { pluginName_ = pluginName; }
	virtual void operator() ( Interface *format ) = 0;
protected:
	void *dlHandle_;
	std::string pluginName_;
};


template<typename Interface>
class DefaultPluginDeleter : public PluginDeleterBase<Interface>
{
public:
	virtual void operator()( Interface *format ) {
		delete format;
#ifdef WIN32

		if( !FreeLibrary( ( HINSTANCE )PluginDeleterBase<Interface>::dlHandle_ ) )
#else
		if ( dlclose( PluginDeleterBase<Interface>::dlHandle_ ) != 0 )
#endif
			std::cerr << "Failed to release plugin " << PluginDeleterBase<Interface>::pluginName_ << " (was loaded at " << PluginDeleterBase<Interface>::dlHandle_ << ")";

		//we cannot use LOG here, because the loggers are gone allready
	}
};
}

template < typename Interface, typename PluginDeleter = _internal::DefaultPluginDeleter<Interface> >
class GenericPluginLoader
{
	friend class isis::util::Singletons;
public:
	typedef isis::util::slist PathListType;
	typedef boost::shared_ptr<Interface> PluginInterfacePointerType;
	typedef std::list<PluginInterfacePointerType> PluginListType;

	static GenericPluginLoader &get() {
		return isis::util::Singletons::get<GenericPluginLoader<Interface>, INT_MAX>();
	}

	static void addPluginSearchPath( const std::string &pluginSearchPath );

	static void setPluginSearchPattern( const std::string &searchPattern ) {
		pluginSearchPattern_ = searchPattern;
		pluginSearchPatternIsSet_ = true;
	}

	static void setPluginLoadingFunctionName( const std::string &pluginLoadingFunctionName ) { pluginLoadingFunctionName_ = pluginLoadingFunctionName; }
	static void setPluginSubSearchPath( const std::string &subSearchPath ) { subSearchPath_ = subSearchPath; }

	PluginListType getPLugins() const { return pluginList_; }

	//signals
	static isis::glance::util::Signal<void ( const Interface * )> signal_plugin_registered;
	static isis::glance::util::Signal<void ( const std::string & )> signal_plugin_registering_failed;
	static isis::glance::util::Signal<void ( const std::string & )> signal_scanning_path;
	static isis::glance::util::Signal<void()> signal_no_search_path;

protected:
	GenericPluginLoader();
	unsigned int findPlugins();
	bool registerPlugin( const PluginInterfacePointerType );

private:
	static PathListType searchPaths_;
	static std::string subSearchPath_;
	static std::string pluginSearchPattern_;
	static std::string pluginLoadingFunctionName_;
	static bool pluginSearchPatternIsSet_;
	PluginListType pluginList_;
};



} // end namespace util
} // end namespace glance
} // end namespace isis

#include "generic_plugin_loader_impl.hpp"

#endif // _ISIS_GLANCE_GENERIC_PLUGIN_LOADER_HPP