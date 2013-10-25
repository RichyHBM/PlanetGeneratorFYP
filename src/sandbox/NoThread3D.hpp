#ifndef NO_THREAD_3D_HPP
#define NO_THREAD_3D_HPP

#include <fstream>
#include <iostream>
#include <string>
#include <iomanip>

#include "framework/Includes.hpp"
#include "framework/Noise/NoiseppNoise.hpp"

#define RUNS 10

void test3dArrayNoThread( const int maxSize )
{
    std::ofstream file;
    std::string filename = "array3DNT.txt";
    file.open( filename.c_str() );
    file << "#Up to " << maxSize << " in increments of 10" << std::endl;

    for( int gr = 10; gr <= maxSize; gr += 10 ) {
        double timeT = 0.0;

        for( int i = 0; i < RUNS; i++ ) {
            sf::Clock clock;

            for( int x = 0; x < gr; x++ ) {
                for( int y = 0; y < gr; y++ ) {
                    for( int z = 0; z < gr; z++ ) {
                        double d = NoisePP.Generate( x, y, z );
                    }
                }
            }

            double d = clock.getElapsedTime().asSeconds();
            timeT += d;
        }

        std::cout << "Avg 3d No Thr " << gr << ": " << timeT/RUNS << std::endl;
        file << gr << ":" << timeT/RUNS << std::endl;
    }

    file.close();
}

#endif