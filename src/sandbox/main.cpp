#include <iostream>

#include "NoThread2D.hpp"
#include "NoThread3D.hpp"
#include "Thread2D.hpp"
#include "Thread2D.hpp"


int main()
{
    //Warm up the CPU
    for ( int n=0; n<100; ++n ) {
        for ( int i=0; i<1000000; ++i ) {
            double d = sqrt( ( double )rand()/RAND_MAX );
        }
    }

    /*test2dArrayNoThread( 100 );
    test2dArrayNoThread(1000);
    test2dArrayNoThread(10000);
    test2dArrayNoThread(100000);

    test3dArrayNoThread(100);
    test3dArrayNoThread(1000);
    test3dArrayNoThread(10000);
    test3dArrayNoThread(100000);
    */
	test2dArrayThread( 100 );
    std::cin.get();
    return 0;
}