#ifndef NOISE_HPP
#define NOISE_HPP

class Noise
{
protected:
    int mSeed;
public:
    Noise( int seed ) {
        mSeed = seed;
    }
    virtual ~Noise() {}

    virtual double Generate( double x ) = 0;
    virtual double Generate( double x, double y ) = 0;
    virtual double Generate( double x, double y, double z ) = 0;
    virtual double Generate( double x, double y, double z, double w ) = 0;

};

static Noise *noise;

#endif