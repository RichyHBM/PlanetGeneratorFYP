#ifndef NOISEPP_NOISE_HPP
#define NOISEPP_NOISE_HPP

#include "Noise.hpp"
#include <noisepp/core/Noise.h>

class NoiseppNoise : public Noise
{
protected:
    noisepp::PerlinModule mPerlin;
    noisepp::ThreadedPipeline1D mPipeline1d;
    noisepp::ThreadedPipeline2D mPipeline2d;
    noisepp::ThreadedPipeline3D mPipeline3d;

    noisepp::ElementID mNoiseID1D;
    noisepp::ElementID mNoiseID2D;
    noisepp::ElementID mNoiseID3D;

    noisepp::Cache *mCache1d;
    noisepp::Cache *mCache2d;
    noisepp::Cache *mCache3d;

    int mThreadCount;
public:
    NoiseppNoise( );
    virtual ~NoiseppNoise();

    virtual double Generate( double x );
    virtual double Generate( double x, double y );
    virtual double Generate( double x, double y, double z );
};

extern NoiseppNoise NoisePP;

#endif