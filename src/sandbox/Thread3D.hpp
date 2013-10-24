#ifndef THREAD_3D_HPP
#define THREAD_3D_HPP

#include <fstream>
#include <iostream>
#include <string>
#include <iomanip>

#include "framework/Includes.hpp"
#include "framework/Noise/NoiseppNoise.hpp"

namespace Threaded3D{
#define RUNS 1000

double ***dArray;

bool finished = false;

static int col = 0;
sf::Mutex mutex;

void generate(int size)
{
	int s;
	mutex.lock();
	{
		s = col++;
		if(col >= size){
			finished = true;
			mutex.unlock();
			return;
		}
	}
	mutex.unlock();
	for( int h = 0; h < size; h++ ) {
		for( int i = 0; i < size; i++ ) {
			dArray[s][h][i] = NoisePP.Generate( s, h, i );
		}
    }
}

#define THREADSCOUNT 2

void test3dArrayThread( int size )
{
    std::ofstream file;
	std::string filename = "array3DThr" + Util::ToString( size ) + ".txt";
    file.open( filename.c_str() );
    double timeT = 0.0;

    for( int i = 0; i < RUNS; i++ ) {
		finished = false;
        dArray = new double**[size];

        for( int h = 0; h < size; h++ ) {
            dArray[h] = new double*[size];
			for( int j = 0; j < size; j++ ) {
				 dArray[h][j] = new double[size];
			}
        }

        
		sf::Thread *threads[THREADSCOUNT];
		for(int h = 0; h < THREADSCOUNT; h++)
			threads[h] = new sf::Thread(&generate, size);

		sf::Clock clock;
		while(!finished){

			for(int h = 0; h < THREADSCOUNT; h++)
            {
				threads[h]->launch();
			}

			for(int h = 0; h < THREADSCOUNT; h++)
			{
				threads[h]->wait();
				delete threads[h];

				threads[h] = new sf::Thread(&generate, size);
			}
		}

        double d = clock.getElapsedTime().asSeconds();
        timeT += d;

		for(int h = 0; h < THREADSCOUNT; h++)
		{
			delete threads[h];
		}

        for( int h = 0; h < size; h++ ) {
			for( int j = 0; j < size; j++ ) {
				 delete[] dArray[h][j];
			}
            delete[] dArray[h];
        }

        delete[] dArray;
        file << d << std::endl;
    }

    std::cout << "Avg 2d Thr " << size << ": " << timeT/RUNS << std::endl;
    file << "Avg: " << timeT/RUNS << std::endl;
    file.close();
}
}
#endif