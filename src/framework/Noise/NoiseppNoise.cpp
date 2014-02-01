#include "NoiseppNoise.hpp"

#include <iostream>
#include <noisepp/utils/NoiseUtils.h>
#include "../Utilities.hpp"

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
NoiseppNoise::NoiseppNoise( )
{
    mDistortion = 0.01;
}

NoiseppNoise::NoiseppNoise( int seed,int oct,double pers, double freq , int qual,double scale , double lacun,double distortion )
{
    SetSeed( seed );
    SetPersistence( pers );
    SetOctaveCount( oct );
    SetFrequency( freq );
    SetQuality( qual );
    SetScale( scale );
    SetLacunarity( lacun );
    SetDistortion( distortion );
    Init();
}

void NoiseppNoise::Init()
{
    mThreadCount = noisepp::utils::System::getNumberOfCPUs ();
    mPipeline1d = new noisepp::ThreadedPipeline1D( mThreadCount );
    mPipeline2d = new noisepp::ThreadedPipeline2D( mThreadCount );
    mPipeline3d = new noisepp::ThreadedPipeline3D( mThreadCount );
    mNoiseID1D = mPerlin.addToPipe ( *mPipeline1d );
    mNoiseID2D = mPerlin.addToPipe ( *mPipeline2d );
    mNoiseID3D = mPerlin.addToPipe ( *mPipeline3d );
    mCache1d = mPipeline1d->createCache();
    mCache2d = mPipeline2d->createCache();
    mCache3d = mPipeline3d->createCache();
}

NoiseppNoise::~NoiseppNoise()
{
    mPipeline1d->freeCache( mCache1d );
    mPipeline2d->freeCache( mCache2d );
    mPipeline3d->freeCache( mCache3d );
    delete mPipeline1d;
    delete mPipeline2d;
    delete mPipeline3d;
    mCache1d = NULL;
    mCache2d = NULL;
    mCache3d = NULL;
}

void NoiseppNoise::ParseArguments( const std::string &arg, const std::string &arg2 )
{
    if( arg == "-noiseseed" ) {
        SetSeed( Util::StrTo<int>( arg2 ) );

    } else if( arg == "-persistance" ) {
        SetPersistence( Util::StrTo<double>( arg2 ) );

    } else if( arg == "-octave" ) {
        SetOctaveCount( Util::StrTo<int>( arg2 ) );

    } else if( arg == "-frequency" ) {
        SetFrequency( Util::StrTo<double>( arg2 ) );

    } else if( arg == "-quality" ) {
        SetQuality( Util::StrTo<int>( arg2 ) );

    } else if( arg == "-scale" ) {
        SetScale( Util::StrTo<double>( arg2 ) );

    } else if( arg == "-lacunarity" ) {
        SetLacunarity( Util::StrTo<double>( arg2 ) );

    } else if( arg == "-distortion" ) {
        SetDistortion( Util::StrTo<double>( arg2 ) );
    }
}

void NoiseppNoise::SetOctaveCount( int oct )
{
    mPerlin.setOctaveCount( oct );
}

void NoiseppNoise::SetPersistence( double pers )
{
    mPerlin.setPersistence( pers );
}
void NoiseppNoise::SetFrequency( double freq )
{
    mPerlin.setFrequency( freq );
}
void NoiseppNoise::SetQuality( int qual )
{
    mPerlin.setQuality( qual );
}
void NoiseppNoise::SetScale( double scale )
{
    mPerlin.setScale( scale );
}
void NoiseppNoise::SetLacunarity( double lacun )
{
    mPerlin.setLacunarity( lacun );
}

void NoiseppNoise::SetDistortion( double distortion )
{
    mDistortion = distortion;
}

void NoiseppNoise::SetSeed( int seed )
{
    mPerlin.setSeed( seed );
}

double NoiseppNoise::Generate( double x )
{
    mPipeline1d->cleanCache( mCache1d );
    return mPipeline1d->getElement( mNoiseID1D )->getValue ( x * mDistortion, mCache1d );
}

double NoiseppNoise::Generate( double x, double y )
{
    mPipeline2d->cleanCache( mCache2d );
    return mPipeline2d->getElement( mNoiseID2D )->getValue ( x * mDistortion, y * mDistortion, mCache2d );
}

double NoiseppNoise::Generate( double x, double y, double z )
{
    mPipeline3d->cleanCache( mCache3d );
    return mPipeline3d->getElement( mNoiseID3D )->getValue ( x * mDistortion, y * mDistortion, z * mDistortion, mCache3d );
}
