#ifndef ACC_NOISE_HPP
#define ACC_NOISE_HPP

#include "Noise.hpp"
#include <acnoise/anl.h>

class AccidentalNoise : public Noise
{
protected:

public:
    AccidentalNoise( int seed );
    virtual ~AccidentalNoise();

    virtual double Generate( double x );
    virtual double Generate( double x, double y );
    virtual double Generate( double x, double y, double z );
    virtual double Generate( double x, double y, double z, double w );
};

#endif