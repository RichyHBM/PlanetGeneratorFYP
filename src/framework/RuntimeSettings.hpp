#ifndef RUNTIMESETTINGS_HPP
#define RUNTIMESETTINGS_HPP

#include "Includes.hpp"
#include <string>

class RuntimeSettings
{
public:
    //Startup settings
    static RuntimeSettings Settings;
    static RuntimeSettings PreviousFrame;

    RuntimeSettings();

    bool DrawLines;
    unsigned int Subdivisions;
    unsigned int PlanetRadius;
    bool LockMouse;
    bool FreezeFrustrum;
    bool DrawHidden;
    glm::vec3 LightDirection;

    int Seed;
    int Octaves;
    double Persistence;
    double Frequency;
    int Quality;
    double Scale;
    double Lacunarity;
    double Distortion;
};

#endif // RUNTIMESETTINGS_HPP
