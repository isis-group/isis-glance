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
 * widget_base.hpp
 *
 * Description:
 *
 *  Created on: Jun 7, 2012
 *      Author: tuerke
 ******************************************************************/
#ifndef _ISIS_GLANCE_WIDGET_BASE_HPP
#define _ISIS_GLANCE_WIDGET_BASE_HPP

#include "data/image_container.hpp"
#include "plugin_interface_base.hpp"

namespace isis
{
namespace glance
{
namespace widget
{
namespace _internal {
struct NoBaseWidget {};
}
/**
* Base class for widgets.
*/

template < class BASE = _internal::NoBaseWidget >
class WidgetBase :
	public plugin::PluginInterfaceBase,
	public BASE,
	public isis::glance::data::ImageContainer
{
public:

protected:
	WidgetBase( BASE *parent ) : BASE( parent ) {}


};

} // end namespace widget
} // end namespace glance
} // end namespace isis


#endif //_ISIS_GLANCE_WIDGET_BASE_HPP