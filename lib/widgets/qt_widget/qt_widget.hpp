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
 * qt_widget.hpp
 *
 * Description:
 *
 *  Created on: Jun 27, 2012
 *      Author: tuerke
 ******************************************************************/
#ifndef _ISIS_GLANCE_WIDGET_PLUGIN_QT_HPP
#define _ISIS_GLANCE_WIDGET_PLUGIN_QT_HPP

#include <util/widget_base.hpp>

#include <QWidget>

namespace isis {
namespace glance {
namespace widget {


class QtWidget : public WidgetBase<QWidget>
{
public:
	QtWidget( QWidget* parent );
	
};

} // end namespace widget
} // end namespace glance
} // end namespace isis

#endif // _ISIS_GLANCE_WIDGET_PLUGIN_QT_HPP