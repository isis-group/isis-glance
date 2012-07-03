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
 * thread.cpp
 *
 * Description:
 *
 *  Created on: Jun 29, 2012
 *      Author: tuerke
 ******************************************************************/
#include "thread.hpp"
#include "common.hpp"
#include <boost/lambda/bind.hpp>
#include <boost/lexical_cast.hpp>

namespace isis
{
namespace glance
{
namespace util
{
Thread::Thread()
	: running_( false ),
	  debugIdent_( "" )
{}

Thread::~Thread()
{
	if( thread_ ) {
		LOG( Debug, verbose_info ) << "Destructing thread " << debugIdent_;
		thread_->join();
	} else {
		LOG( Runtime, warning ) << "Destructing thread that has not been started!";
	}
}


void Thread::start()
{
	signal_created.call();
	thread_.reset( new boost::thread( boost::ref( *this ) ) );

	if( debugIdent_.empty() ) {
		debugIdent_ = boost::lexical_cast< std::string, boost::thread::id>( thread_->get_id() );
	}
	mutex_.lock();
	LOG( Debug, verbose_info ) << "Created thread " << debugIdent_;
	mutex_.unlock();
}

void Thread::operator() ()
{
	signal_started.call();
	mutex_.lock();
	LOG( Debug, verbose_info ) << "Started thread " << debugIdent_;
	mutex_.unlock();
	running_ = true;
	run();
	signal_finished.call();
	mutex_.lock();
	LOG( Debug, verbose_info ) << "Finished thread" << debugIdent_;
	mutex_.unlock();
	running_ = false;
}


void Thread::interrupt()
{
	if( thread_ ) {
		LOG( Debug, verbose_info ) << "Interrupting thread " << debugIdent_;
		signal_interrupted.call();
		thread_->interrupt();
	} else {
		LOG( Runtime, warning ) << "Trying to interrupt a thread that has not been started!";
	}
}
void Thread::join()
{
	if( thread_ ) {
		mutex_.lock();
		LOG( Debug, verbose_info ) << "Joining thread " << debugIdent_;
		mutex_.unlock();
		signal_joined.call();
		thread_->join();
	} else {
		LOG( Runtime, warning ) << "Trying to join a thread that has not been started!";
	}
}

void Thread::yield()
{
	if( thread_ ) {
		signal_yielded.call();
		boost::this_thread::yield();
	} else {
		LOG( Runtime, warning ) << "Trying to yield a thread hat has not been started!";
	}
}


void Thread::sleep ( const size_t &milliseconds )
{
	if( thread_ ) {
		LOG( Debug, verbose_info ) << "Sending thread " << debugIdent_
								   << " to sleep for " << milliseconds << " ms";
		signal_sleep.call( milliseconds );
		boost::this_thread::sleep ( boost::posix_time::millisec( milliseconds ) );
	} else {
		LOG( Runtime, warning ) << "Trying to make a thread sleeping that has not been started!";
	}
}



} // end namespace util
} // end namespace glance
} // end namespace isis