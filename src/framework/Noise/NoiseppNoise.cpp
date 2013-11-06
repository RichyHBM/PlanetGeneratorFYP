#include "NoiseppNoise.hpp"

#include <iostream>
#include <noisepp/utils/NoiseUtils.h>
#include "../Utilities.hpp"

NoiseppNoise NoisePP;
//
// Defaults are
// Frequency	=	1
// Octaves		=	6
// Seed			=	0
// Quality		=	1
// Lacunarity	=	2
// Persistence	=	0.5
// Scale		=	2.12
//
NoiseppNoise::NoiseppNoise( ) : mPipeline1d( 2 ), mPipeline2d( 2 ), mPipeline3d( 2 )
{
    mThreadCount = noisepp::utils::System::getNumberOfCPUs ();

    if ( mThreadCount > 2 ) {
        mPipeline1d = noisepp::ThreadedPipeline1D( mThreadCount );
        mPipeline2d = noisepp::ThreadedPipeline2D( mThreadCount );
        mPipeline3d = noisepp::ThreadedPipeline3D( mThreadCount );
    }    

    mNoiseID1D = mPerlin.addToPipe ( mPipeline1d );
    mNoiseID2D = mPerlin.addToPipe ( mPipeline2d );
    mNoiseID3D = mPerlin.addToPipe ( mPipeline3d );
    mCache1d = mPipeline1d.createCache();
    mCache2d = mPipeline2d.createCache();
    mCache3d = mPipeline3d.createCache();

	mDistortion = 1.0;
}

NoiseppNoise::~NoiseppNoise()
{
    mPipeline1d.freeCache( mCache1d );
    mPipeline2d.freeCache( mCache2d );
    mPipeline3d.freeCache( mCache3d );
    mCache1d = NULL;
    mCache2d = NULL;
    mCache3d = NULL;
}

void NoiseppNoise::ParseArguments( int argc, const char *argv[] )
{
	for(int i = 1; i < argc; i++)
	{
		if(argv[i] == "-seed" && argc > i+1)
		{
			SetSeed( Util::StrTo<int>(argv[i+1]) );
		}
		else if(argv[i] == "-persistance" && argc > i+1)
		{
			SetPersistence( Util::StrTo<double>(argv[i+1]));
		}
		else if(argv[i] == "-octave" && argc > i+1)
		{
			SetOctaveCount( Util::StrTo<int>(argv[i+1]));
		}
		else if(argv[i] == "-frequency" && argc > i+1)
		{
			SetFrequency( Util::StrTo<double>(argv[i+1]));
		}
		else if(argv[i] == "-quality" && argc > i+1)
		{
			SetQuality( Util::StrTo<int>(argv[i+1]));
		}
		else if(argv[i] == "-scale" && argc > i+1)
		{
			SetScale( Util::StrTo<double>(argv[i+1]));
		}
		else if(argv[i] == "-lacunarity" && argc > i+1)
		{
			SetLacunarity( Util::StrTo<double>(argv[i+1]));
		}
		else if(argv[i] == "-distortion" && argc > i+1)
		{
			SetDistortion( Util::StrTo<double>(argv[i+1]));
		}
	}
}

void NoiseppNoise::SetOctaveCount(int oct)
{
	mPerlin.setOctaveCount( oct );
}

void NoiseppNoise::SetPersistence(double pers)
{
	mPerlin.setPersistence(pers);	
}
void NoiseppNoise::SetFrequency(double freq)
{
	mPerlin.setFrequency(freq);
}
void NoiseppNoise::SetQuality(int qual)
{
	mPerlin.setQuality(qual);	
}
void NoiseppNoise::SetScale(double scale)
{
	mPerlin.setScale(scale);	
}
void NoiseppNoise::SetLacunarity(double lacun)
{
	mPerlin.setLacunarity(lacun);
}

void NoiseppNoise::SetDistortion(double distortion)
{
	mDistortion = distortion;
}

void NoiseppNoise::SetSeed(int seed)
{
	mPerlin.setSeed(seed);
	mPipeline1d.setSeed(seed);
	mPipeline2d.setSeed(seed);
	mPipeline3d.setSeed(seed);
}

double NoiseppNoise::Generate( double x )
{
    mPipeline1d.cleanCache( mCache1d );
    return mPipeline1d.getElement( mNoiseID1D )->getValue ( x * mDistortion, mCache1d );
}

double NoiseppNoise::Generate( double x, double y )
{
    mPipeline2d.cleanCache( mCache2d );
    return mPipeline2d.getElement( mNoiseID2D )->getValue ( x * mDistortion, y * mDistortion, mCache2d );
}

double NoiseppNoise::Generate( double x, double y, double z )
{
    mPipeline3d.cleanCache( mCache3d );
    return mPipeline3d.getElement( mNoiseID3D )->getValue ( x * mDistortion, y * mDistortion, z * mDistortion, mCache3d );
}
