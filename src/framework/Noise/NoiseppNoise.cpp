#include "NoiseppNoise.hpp"

#include <iostream>
#include <noisepp/utils/NoiseUtils.h>

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

NoiseppNoise NoisePP = NoiseppNoise();

NoiseppNoise::NoiseppNoise( ) : mPipeline1d(2), mPipeline2d(2), mPipeline3d(2)
{
	mThreadCount = noisepp::utils::System::getNumberOfCPUs ();
	if (mThreadCount > 2)
	{
		mPipeline1d = noisepp::ThreadedPipeline1D(mThreadCount);
		mPipeline2d = noisepp::ThreadedPipeline2D(mThreadCount);
		mPipeline3d = noisepp::ThreadedPipeline3D(mThreadCount);
	}

	mNoiseID1D = mPerlin.addToPipe (mPipeline1d);
	mNoiseID2D = mPerlin.addToPipe (mPipeline2d);
	mNoiseID3D = mPerlin.addToPipe (mPipeline3d);

	mCache1d = mPipeline1d.createCache();
	mCache2d = mPipeline2d.createCache();
	mCache3d = mPipeline3d.createCache();
}

NoiseppNoise::~NoiseppNoise()
{
	mPipeline1d.freeCache(mCache1d);
	mPipeline2d.freeCache(mCache2d);
	mPipeline3d.freeCache(mCache3d);
}

double NoiseppNoise::Generate( double x )
{
    return mPipeline1d.getElement(mNoiseID1D)->getValue (x, mCache1d);
}

double NoiseppNoise::Generate( double x, double y )
{
	return mPipeline2d.getElement(mNoiseID2D)->getValue (x, y, mCache2d);
}

double NoiseppNoise::Generate( double x, double y, double z )
{
    return mPipeline3d.getElement(mNoiseID3D)->getValue (x, y, z, mCache3d);
}
