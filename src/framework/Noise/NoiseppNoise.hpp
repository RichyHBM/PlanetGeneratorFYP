#ifndef NOISEPP_NOISE_HPP
#define NOISEPP_NOISE_HPP

#include <noisepp/core/Noise.h>
#include <string>

class NoiseppNoise
{
protected:
    noisepp::PerlinModule mPerlin;
    noisepp::ThreadedPipeline1D *mPipeline1d;
    noisepp::ThreadedPipeline2D *mPipeline2d;
    noisepp::ThreadedPipeline3D *mPipeline3d;

    noisepp::ElementID mNoiseID1D;
    noisepp::ElementID mNoiseID2D;
    noisepp::ElementID mNoiseID3D;

    noisepp::Cache *mCache1d;
    noisepp::Cache *mCache2d;
    noisepp::Cache *mCache3d;

    int mThreadCount;
    double mDistortion;
public:
    NoiseppNoise( );
    ~NoiseppNoise();
    void Init();
    void SetSeed( int seed );
    void SetOctaveCount( int oct );
    void SetPersistence( double pers );
    void SetFrequency( double freq );
    void SetQuality( int qual );
    void SetScale( double scale );
    void SetLacunarity( double lacun );
    void SetDistortion( double distortion );

    void ParseArguments( const std::string &arg, const std::string &arg2 );

    double Generate( double x );
    double Generate( double x, double y );
    double Generate( double x, double y, double z );
};

extern NoiseppNoise NoisePP;

#endif