#include <iostream>

#include "NoThread2D.hpp"
#include "NoThread3D.hpp"
#include "Thread2D.hpp"
#include "Thread3D.hpp"


int main()
{
    //Warm up the CPU
    for ( int n=0; n<100; ++n ) {
        for ( int i=0; i<1000000; ++i ) {
            double d = sqrt( ( double )rand()/RAND_MAX );
        }
    }

    test2dArrayNoThread( 100 );
    test2dArrayNoThread(1000);
    test2dArrayNoThread(10000);
    test2dArrayNoThread(100000);

    test3dArrayNoThread(100);
    test3dArrayNoThread(1000);
    test3dArrayNoThread(10000);
    test3dArrayNoThread(100000);
    
	test2dArrayThread(100);
	test2dArrayThread(1000);
    test2dArrayThread(10000);
    test2dArrayThread(100000);

	Threaded3D::test3dArrayThread(100);
	Threaded3D::test3dArrayThread(1000);
    Threaded3D::test3dArrayThread(10000);
    Threaded3D::test3dArrayThread(100000);
    
	std::cin.get();
    return 0;
}