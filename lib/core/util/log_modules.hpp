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
 * log_modules.hpp
 *
 * Description:
 *
 *  Created on: Jun 29, 2012
 *      Author: tuerke
 ******************************************************************/
#ifndef _ISIS_GLANCE_LOG_MOUDLES_HPP
#define _ISIS_GLANCE_LOG_MOUDLES_HPP

/// @cond _internal
namespace isis
{
namespace glance
{

struct CoreLog {static const char *name() {return "GlanceCore";}; enum {use = _ENABLE_LOG};};
struct CoreDebug {static const char *name() {return "GlanceCoreDebug";}; enum {use = _ENABLE_DEBUG};};

struct DataLog {static const char *name() {return "GlanceData";}; enum {use = _ENABLE_LOG};};
struct DataDebug {static const char *name() {return "GlanceDataDebug";}; enum {use = _ENABLE_DEBUG};};

} // end namespace glance
} // end namespace isis
/// @endcond

#endif //_ISIS_GLANCE_LOG_MOUDLES_HPP