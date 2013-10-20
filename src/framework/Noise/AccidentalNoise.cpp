#include "AccidentalNoise.hpp"

AccidentalNoise::AccidentalNoise( int seed ) : Noise( seed )
{
}

AccidentalNoise::~AccidentalNoise()
{
}

double AccidentalNoise::Generate( double x )
{
    return 0.0;
}

double AccidentalNoise::Generate( double x, double y )
{
    return 0.0;
}

double AccidentalNoise::Generate( double x, double y, double z )
{
    return 0.0;
}

double AccidentalNoise::Generate( double x, double y, double z, double w )
{
    return 0.0;
}