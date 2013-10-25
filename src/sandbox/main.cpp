#include <iostream>

#include "NoThread2D.hpp"
#include "NoThread3D.hpp"
#include "Thread2D.hpp"
#include "Thread3D.hpp"

#include "SOIL.h"

int main()
{
    for( int x = 0; x < 10; x++ ) {
        for( int y = 0; y < 10; y++ ) {
            std::cout << std::setw( 10 ) << Util::ToString( NoisePP.Generate( x*0.01,y*0.01 ), 2 );
        }

        std::cout << std::endl;
    }

    std::cin.get();
    return 0;
}