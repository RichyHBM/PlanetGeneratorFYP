#include <iostream>
#include <iomanip>
#include <algorithm>
#include <string>
#include <vector>
#include <sstream>

#include "SOIL.h"
#include "framework/Noise/NoiseppNoise.hpp"

double distortion = 0.01;
std::string file = "new_terrain.bmp";

using namespace std;

double toD(std::string s)
{
	std::istringstream os(s);
    double d;
    os >> d;
	return d;
}

int main( int argc, const char *argv[])
{
	if(argc < 10){
		std::cout << "Nope"<< std::endl;
		std::cin.get();
		return 1;
	}

	std::vector<std::string> params(argv+1, argv+argc);


	if( toD(params[0]) != 0.0)
		NoisePP.SetSeed(toD(params[0]));

	if( toD(params[1]) != 0.0)
		NoisePP.SetOctaveCount(toD(params[1]));

	if( toD(params[2]) != 0.0)
		NoisePP.SetPersistence(toD(params[2]));

	if( toD(params[3]) != 0.0)
		NoisePP.SetFrequency(toD(params[3]));

	if( toD(params[4]) != 0.0)
		NoisePP.SetQuality(toD(params[4]));

	if( toD(params[5]) != 0.0)
		NoisePP.SetScale(toD(params[5]));

	if( toD(params[6]) != 0.0)
		NoisePP.SetLacunarity(toD(params[6]));

	if( toD(params[7]) != 0.0)
		distortion = toD(params[7]);

	if( params[8] != " ")
		file = params[8];

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
			image[i + j * mWidth] = min( NoisePP.Generate( i*distortion, j*distortion ) * 127 , 255);
		}
    }

	SOIL_save_image	(file.c_str(),	SOIL_SAVE_TYPE_BMP,	mWidth, mHeight, 1,	image);

	delete[] image;
    return 0;
}