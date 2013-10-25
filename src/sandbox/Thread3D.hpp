#ifndef THREAD_3D_HPP
#define THREAD_3D_HPP

#include <fstream>
#include <iostream>
#include <string>
#include <iomanip>

#include "framework/Includes.hpp"
#include "framework/Noise/NoiseppNoise.hpp"

namespace Threaded3D
{

    bool finished = false;

    static int col = 0;
    sf::Mutex mutex;

    void generate( int size )
    {
        int s;
        mutex.lock();
        {
            s = col++;

            if( col >= size ) {
                finished = true;
                mutex.unlock();
                return;
            }
        }
        mutex.unlock();

        for( int h = 0; h < size; h++ ) {
            for( int i = 0; i < size; i++ ) {
                double d = NoisePP.Generate( s, h, i );
            }
        }
    }

#define THREADSCOUNT 2
#define RUNS 10
    void test3dArrayThread( int maxSize )
    {
        std::ofstream file;
        std::string filename = "array3DThr.txt";
        file.open( filename.c_str() );
        file << "#Up to " << maxSize << " in increments of 10" << std::endl;

        for( int gr = 10; gr <= maxSize; gr += 10 ) {
            double timeT = 0.0;

            for( int i = 0; i < RUNS; i++ ) {
                finished = false;
                col = 0;
                sf::Thread *threads[THREADSCOUNT];

                for( int h = 0; h < THREADSCOUNT; h++ ) {
                    threads[h] = new sf::Thread( &generate, gr );
                }

                sf::Clock clock;

                while( !finished ) {
                    for( int h = 0; h < THREADSCOUNT; h++ ) {
                        threads[h]->launch();
                    }

                    for( int h = 0; h < THREADSCOUNT; h++ ) {
                        threads[h]->wait();
                        delete threads[h];
                        threads[h] = new sf::Thread( &generate, gr );
                    }
                }

                double d = clock.getElapsedTime().asSeconds();
                timeT += d;

                for( int h = 0; h < THREADSCOUNT; h++ ) {
                    threads[h]->wait();
                    delete threads[h];
                }
            }

            std::cout << "Avg 3d Thr " << gr << ": " << timeT/RUNS << std::endl;
            file << gr << ":" << timeT/RUNS << std::endl;
        }

        file.close();
    }
}
#endif