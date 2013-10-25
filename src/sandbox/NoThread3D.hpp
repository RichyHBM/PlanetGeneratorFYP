#ifndef NO_THREAD_3D_HPP
#define NO_THREAD_3D_HPP

#include <fstream>
#include <iostream>
#include <string>
#include <iomanip>

#include "framework/Includes.hpp"
#include "framework/Noise/NoiseppNoise.hpp"

#define RUNS 1000

void test3dArrayNoThread( const int size )
{
    std::ofstream file;
    std::string filename = "array3DNT" + Util::ToString( size ) + ".txt";
    file.open( filename.c_str() );
    double timeT = 0.0;

    for( int i = 0; i < RUNS; i++ ) {
        sf::Clock clock;

        for( int x = 0; x < size; x++ ) {
            for( int y = 0; y < size; y++ ) {
                for( int z = 0; z < size; z++ ) {
                    double d = NoisePP.Generate( x, y, z );
                }
            }
        }

        double d = clock.getElapsedTime().asSeconds();
        timeT += d;
        file << d << std::endl;
    }

    std::cout << "Avg 3d NT " << size << ": " << timeT/RUNS << std::endl;
    file << "Avg: " << timeT/RUNS << std::endl;
    file.close();
}

#endif