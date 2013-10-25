#ifndef NO_THREAD_2D_HPP
#define NO_THREAD_2D_HPP

#include <fstream>
#include <iostream>
#include <string>
#include <iomanip>

#include "framework/Includes.hpp"
#include "framework/Noise/NoiseppNoise.hpp"

#define RUNS 10

void test2dArrayNoThread( const int maxSize )
{
    std::ofstream file;
    std::string filename = "array2DNT.txt";
    file.open( filename.c_str() );
    file << "#Up to " << maxSize << " in increments of 10" << std::endl;

    for( int gr = 10; gr <= maxSize; gr += 10 ) {
        double timeT = 0.0;

        for( int i = 0; i < RUNS; i++ ) {
            sf::Clock clock;

            for( int x = 0; x < gr; x++ ) {
                for( int y = 0; y < gr; y++ ) {
                    double d = NoisePP.Generate( x, y );
                }
            }

            double d = clock.getElapsedTime().asSeconds();
            timeT += d;
        }

        std::cout << "Avg 2d No Thr " << gr << ": " << timeT/RUNS << std::endl;
        file << gr << ":" << timeT/RUNS << std::endl;
    }

    file.close();
}

#endif