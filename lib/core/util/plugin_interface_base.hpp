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
 * plugin_interface_base.hpp
 *
 * Description:
 *
 *  Created on: Jul 5, 2012
 *      Author: tuerke
 ******************************************************************/
#ifndef _ISIS_GLANCE_PLUGIN_INTERFACE_BASE_HPP
#define _ISIS_GLANCE_PLUGIN_INTERFACE_BASE_HPP

#include <string>
#include "generic_plugin_loader.hpp"

namespace isis
{
namespace glance
{
namespace plugin
{

class PluginInterfaceBase
{

public:
	const std::string &getPluginPath() const { return pluginPath_; }
	const std::string &getPluginFile() const { return pluginFile_; }

	void setPluginPath( const std::string pluginPath ) { pluginPath_ = pluginPath; }
	void setPluginFile( const std::string pluginFile ) { pluginFile_ = pluginFile; }
private:
	std::string pluginPath_;
	std::string pluginFile_;
};

} // end namespace plugin
} // end namespace glance
} // end namespace plugin

#endif // _ISIS_GLANCE_PLUGIN_INTERFACE_BASE_HPP