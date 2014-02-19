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
    unsigned int WaterRadius;
    bool LockMouse;
    bool FreezeFrustrum;
    bool DrawHidden;
    bool RealtimeRebuild;
    glm::vec3 LightDirection;

    glm::vec4 WaterColor;

    int Seed;
    int Octaves;
    double Persistence;
    double Frequency;
    int Quality;
    double Scale;
    double Lacunarity;
    double Distortion;

    float GrassHeight;
    float DirtHeight;
    float SnowHeight;
    float WaveSize;

    float SinAmount;
};

#endif // RUNTIMESETTINGS_HPP
