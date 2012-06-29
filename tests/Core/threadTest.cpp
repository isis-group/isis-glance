#include <iostream>
#include <stdio.h>

#include "util/thread.hpp"




int main(int argc, char **argv)
{

	const int counter = 1000;
	
	class MyThread : public isis::glance::Thread
	{
		int iterations_;
	public:
		MyThread( int iterations ) : iterations_(iterations)  {}
        virtual void operator() () {
			for( int i = 0; i < iterations_; i++ ) {
				std::cout << "\033[1;31mthread\033[0m " << std::flush;
			}
		};
		
	};
	
	MyThread thread(counter);
	thread.start();
	thread.interrupt();
	thread.join();
	
	for( unsigned i = 0; i < counter; i++ ) {
		std::cout << "\033[1;34mmain\033[0m " << std::flush;
	}
	std::cout << std::endl;
	getchar();
	return 0;
}
