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
 * generic_plugin_loader_impl.hpp
 *
 * Description:
 *
 *  Created on: Jul 5, 2012
 *      Author: tuerke
 ******************************************************************/
#include "generic_plugin_loader.hpp"
#include "boost/regex.hpp"

#include <dlfcn.h>

namespace isis {
namespace glance {
namespace util {
namespace _internal
{
template<typename Interface>
struct pluginDeleter {
	void *m_dlHandle;
	std::string m_pluginName;
	pluginDeleter( void *dlHandle, std::string pluginName ): m_dlHandle( dlHandle ), m_pluginName( pluginName ) {}
	void operator()( Interface *format ) {
		delete format;
#ifdef WIN32

		if( !FreeLibrary( ( HINSTANCE )m_dlHandle ) )
#else
		if ( dlclose( m_dlHandle ) != 0 )
#endif
			std::cerr << "Failed to release plugin " << m_pluginName << " (was loaded at " << m_dlHandle << ")";

		//we cannot use LOG here, because the loggers are gone allready
	}
};
}
template<typename Interface> typename GenericPluginLoader<Interface>::PathListType GenericPluginLoader<Interface>::searchPaths_;
template<typename Interface> std::string GenericPluginLoader<Interface>::pluginSearchPattern_;
template<typename Interface> bool GenericPluginLoader<Interface>::pluginSearchPatternIsSet_ = false;
template<typename Interface> std::string GenericPluginLoader<Interface>::pluginLoadingFunctionName_ = "loadPlugin";
template<typename Interface> std::string GenericPluginLoader<Interface>::subSearchPath_;

template<typename Interface> isis::glance::util::Signal<void( const Interface* )> GenericPluginLoader<Interface>::signal_plugin_registered;
template<typename Interface> isis::glance::util::Signal<void( const Interface* )> GenericPluginLoader<Interface>::signal_plugin_registering_failed;
template<typename Interface> isis::glance::util::Signal<void( const std::string& )> GenericPluginLoader<Interface>::signal_scanning_path;
template<typename Interface> isis::glance::util::Signal<void()> GenericPluginLoader<Interface>::signal_no_search_path;

template<typename Interface>
GenericPluginLoader<Interface>::GenericPluginLoader()
{
	//use this as standard plugin search path
	const char* homeSearchPath = getenv("HOME");
	if( homeSearchPath ) {
		addPluginSearchPath( homeSearchPath );
	}
	if( pluginSearchPatternIsSet_ ) {
		findPlugins();
	} else {
		LOG( Runtime, error ) << "Plugin search pattern is not set. Please call GenericPluginLoader::setPluginSearchPattern before.";
	}
}

template<typename Interface>
bool
GenericPluginLoader<Interface>::registerPlugin( const PluginInterfacePointerType plugin ) {
	if( !plugin ) {
		return false;
	} else {
		pluginList_.push_back( plugin );
		return true;
	}
		
}

template<typename Interface>
unsigned int
GenericPluginLoader<Interface>::findPlugins() {
	unsigned int ret = 0;
	bool pathOk;

	if( searchPaths_.empty() ) {
		LOG( Runtime, warning ) << "No pluginpath to search for.";
		signal_no_search_path();
	}
	
	BOOST_FOREACH( PathListType::const_reference path, searchPaths_ ) {
		boost::filesystem::path pPath( path );
		pPath /= subSearchPath_;
		pathOk = true;
		if( !boost::filesystem::exists( pPath ) ) {
			LOG( Runtime, warning ) << "Pluginpath " << isis::util::MSubject( pPath.native_file_string() ) << " not found!";
			pathOk = false;
		}

		if( !boost::filesystem::is_directory( pPath ) && pathOk ) {
			LOG( Runtime, warning ) << isis::util::MSubject( pPath.native_file_string() ) << " is not a directory!";
			pathOk = false;
		}

		signal_scanning_path( pPath.native_file_string() );
		LOG( Runtime, info ) << "Scanning " << isis::util::MSubject( pPath ) << " for plugins...";

		if( pathOk ) {
			boost::regex pluginFilter( pluginSearchPattern_ );
			for ( boost::filesystem::directory_iterator itr( pPath ); itr != boost::filesystem::directory_iterator(); ++itr ) {
				if ( boost::filesystem::is_directory( *itr ) )continue;
				
				if ( boost::regex_match( itr->path().leaf(), pluginFilter ) ) {
					const std::string pluginName = itr->path().file_string();
#ifdef WIN32
					HINSTANCE handle = LoadLibrary( pluginName.c_str() );
#else
					void *handle = dlopen( pluginName.c_str(), RTLD_NOW );
#endif
					if( handle ) {
#ifdef WIN32
						Interface* ( *loadPlugin_func )() = ( Interface* ( * )() )GetProcAddress( handle, pluginLoadingFunctionName_.c_str() );
#else
						Interface* ( *loadPlugin_func )() = ( Interface* ( * )() )dlsym( handle, pluginLoadingFunctionName_.c_str() );
#endif
						if ( loadPlugin_func ) {
							PluginInterfacePointerType plugin_class( loadPlugin_func(), _internal::pluginDeleter<Interface>( handle, pluginName ) );
							if ( registerPlugin( plugin_class ) ) {
								plugin_class->setPluginPath( pPath.native_file_string() );
								plugin_class->setPluginFile( pluginName );
								ret++;
								signal_plugin_registered( plugin_class.get() );
							} else {
								signal_plugin_registering_failed( plugin_class.get() );
								LOG( Runtime, warning ) << "Failed to register plugin " << isis::util::MSubject( pluginName );
							}
						} else {
#ifdef WIN32
							LOG( Runtime, warning )
									<< "Could not get format factory function from " << util::MSubject( pluginName );
							FreeLibrary( handle );
#else
							LOG( Runtime, warning )
									<< "Could not get format factory function from " << isis::util::MSubject( pluginName ) << ":" << isis::util::MSubject( dlerror() );
							dlclose( handle );
#endif
						}
					} else {
#ifdef WIN32
						LOG( Runtime, warning ) << "Could not load library " << isis::util::MSubject( pluginName );

#else
						LOG( Runtime, warning ) << "Could not load library " << isis::util::MSubject( pluginName ) << ":" <<  isis::util::MSubject( dlerror() );
#endif
					}
				} else {
					LOG( Runtime, verbose_info )
						<< "Ignoring " << isis::util::MSubject( itr->path() )
						<< " because it doesn't match " << pluginFilter.str();
				}
			}
		}
	}
	return ret;
}

template<typename Interface>
void
GenericPluginLoader<Interface>::addPluginSearchPath( const std::string &pluginSearchPath )
{
	boost::filesystem::path p( pluginSearchPath );
	if( !boost::filesystem::exists( pluginSearchPath ) ) {
		LOG( Runtime, warning ) << "Plugin search path "
			<< p.directory_string() << " does not exist. Will not add it!";
	} else {
		searchPaths_.push_back( pluginSearchPath );
	}
}

} // end namespace util
} // end namespace glance
} // end namespace isis