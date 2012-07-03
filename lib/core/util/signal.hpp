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
 * signals.hpp
 *
 * Description:
 *
 *  Created on: Jun 22, 2012
 *      Author: tuerke
 ******************************************************************/
#ifndef _ISIS_GLANCE_SIGNALS_HPP
#define _ISIS_GLANCE_SIGNALS_HPP

#include <boost/signals2.hpp>

#include "data/image.hpp"
#include "data/image_container.hpp"

namespace isis
{
namespace glance
{
namespace util
{
/**
 *	Copyable Signal class that encapsulates a boost::signals2::signal
 */
template<typename SIGNATURE>
class Signal
{
public:
	Signal() : signal_( boost::shared_ptr<boost::signals2::signal<SIGNATURE> >( new boost::signals2::signal<SIGNATURE> ) ) {}
	
	void call() { (*signal_)(); }
	
	template<typename TYPE>
	void call( const TYPE &arg1 ) { (*signal_)( arg1 ); }

	template<typename TYPE1, typename TYPE2>
	void call( const TYPE1 &arg1, const TYPE2 &arg2 ) { (*signal_)( arg1, arg2 ); }

	template<typename TYPE1, typename TYPE2, typename TYPE3>
	void call( const TYPE1 &arg1, const TYPE2 &arg2, const TYPE3 &arg3 ) { (*signal_)( arg1, arg2, arg3 ); }

	template<typename TYPE1, typename TYPE2, typename TYPE3, typename TYPE4>
	void call( const TYPE1 &arg1, const TYPE2 &arg2, const TYPE3 &arg3, const TYPE4 &arg4 ) { (*signal_)( arg1, arg2, arg3, arg4 ); }
	
	template<typename TYPE1, typename TYPE2, typename TYPE3, typename TYPE4, typename TYPE5>
	void call( const TYPE1 &arg1, const TYPE2 &arg2, const TYPE3 &arg3, const TYPE4 &arg4, const TYPE5 &arg5 ) { (*signal_)( arg1, arg2, arg3, arg4, arg5 ); }

	const boost::signals2::signal< SIGNATURE > &get() const { return *signal_; }
	boost::signals2::signal< SIGNATURE > &get() { return *signal_; }
	
private:
	boost::shared_ptr<boost::signals2::signal< SIGNATURE > > signal_;
};

namespace signals
{

//image signals
static boost::signals2::signal<void ( const data::Image *, const data::Image::ImageContentType & )> image_content_changed;

} // end namespace signal
} // end namespace util
} // end namespace glance
} // end namespace isis

#endif // _ISIS_GLANCE_SIGNALS_HPP