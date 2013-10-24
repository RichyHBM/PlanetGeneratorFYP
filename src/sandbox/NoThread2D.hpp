#ifndef NO_THREAD_2D_HPP
#define NO_THREAD_2D_HPP

#include <fstream>
#include <iostream>
#include <string>
#include <iomanip>

#include "framework/Includes.hpp"
#include "framework/Noise/NoiseppNoise.hpp"

#define RUNS 1000

void test2dArrayNoThread( const int size )
{
    std::ofstream file;
	std::string filename = "array2DNT" + Util::ToString( size ) + ".txt";
    file.open( filename.c_str() );
    double timeT = 0.0;

    for( int i = 0; i < RUNS; i++ ) {
        double **dArray	= new double*[size];

        for( int h = 0; h < size; h++ ) {
            dArray[h] = new double[size];
        }

        sf::Clock clock;

        for( int x = 0; x < size; x++ ) {
            for( int y = 0; y < size; y++ ) {
                dArray[x][y] = NoisePP.Generate( x, y );
            }
        }

        double d = clock.getElapsedTime().asSeconds();
        timeT += d;

        for( int h = 0; h < size; h++ ) {
            delete[] dArray[h];
        }

        delete[] dArray;
        file << d << std::endl;
    }

    std::cout << "Avg 2d NT " << size << ": " << timeT/RUNS << std::endl;
    file << "Avg: " << timeT/RUNS << std::endl;
    file.close();
}

#endif