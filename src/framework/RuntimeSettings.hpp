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
    unsigned int Distortions;
    unsigned int PlanetRadius;
    bool LockMouse;
    unsigned int Seed;
    bool FreezeFrustrum;
    bool DrawHidden;
    float DistortionSize;
    float RealtimeRebuild;
    glm::vec3 LightDirection;
};

#endif // RUNTIMESETTINGS_HPP
