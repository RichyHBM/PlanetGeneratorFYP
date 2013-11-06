#include <iostream>
#include <iomanip>
#include <algorithm>
#include <string>
#include <vector>
#include <sstream>

#include "SOIL.h"
#include "framework/Noise/NoiseppNoise.hpp"
#include "framework/Utilities.hpp"

double distortion = 0.01;
std::string file = "new_terrain.bmp";

using namespace std;

int main( int argc, const char *argv[] )
{
    if( argc < 10 ) {
        std::cout << "Not enought arguments"<< std::endl;
        std::cin.get();
        return 1;
    }

    std::vector<std::string> params( argv+1, argv+argc );

    if( Util::StrTo<int>( params[0] ) != 0 ) {
        NoisePP.SetSeed( Util::StrTo<int>( params[0] ) );
    }

    if( Util::StrTo<int>( params[1] ) != 0 ) {
        NoisePP.SetOctaveCount( Util::StrTo<int>( params[1] ) );
    }

    if( Util::StrTo<double>( params[2] ) != 0.0 ) {
        NoisePP.SetPersistence( Util::StrTo<double>( params[2] ) );
    }

    if( Util::StrTo<double>( params[3] ) != 0.0 ) {
        NoisePP.SetFrequency( Util::StrTo<double>( params[3] ) );
    }

    if( Util::StrTo<int>( params[4] ) != 0 ) {
        NoisePP.SetQuality( Util::StrTo<int>( params[4] ) );
    }

    if( Util::StrTo<double>( params[5] ) != 0.0 ) {
        NoisePP.SetScale( Util::StrTo<double>( params[5] ) );
    }

    if( Util::StrTo<double>( params[6] ) != 0.0 ) {
        NoisePP.SetLacunarity( Util::StrTo<double>( params[6] ) );
    }

    if( Util::StrTo<double>( params[7] ) != 0.0 ) {
        distortion = Util::StrTo<double>( params[7] );
    }

    if( params[8] != " " || params[8] != "" ) {
        file = params[8];
    }

    // Frequency	=	1
    // Octaves		=	6
    // Seed			=	0
    // Quality		=	1
    // Lacunarity	=	2
    // Persistence	=	0.5
    // Scale		=	2.12
    const int mWidth = 512;
    const int mHeight = 512;
    unsigned char *image = new unsigned char[mHeight * mWidth];

    for( int j = 0; j < mHeight; j++ ) {
        for( int i = 0; i < mWidth; i++ ) {
            image[i + j * mWidth] = ( unsigned char ) min( NoisePP.Generate( i*distortion, j*distortion ) * 127.5 , 255.0 );
        }
    }

    SOIL_save_image	( file.c_str(),	SOIL_SAVE_TYPE_BMP,	mWidth, mHeight, 1,	image );
    delete[] image;
    return 0;
}