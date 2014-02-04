#include "RuntimeSettings.hpp"

#include <cstdlib>

RuntimeSettings RuntimeSettings::Settings;
RuntimeSettings RuntimeSettings::PreviousFrame;

RuntimeSettings::RuntimeSettings()
{
    DrawLines = false;
    Subdivisions = 4;
    PlanetRadius = 200;
    LockMouse = true;
    FreezeFrustrum = false;
    DrawHidden = true;
    LightDirection = glm::vec3( 0,0,-1 );
    RealtimeRebuild = false;
    Seed = 1234;
    Octaves = 6;
    Persistence = 0.5;
    Frequency = 2;
    Quality = 1;
    Scale = 0.025;
    Lacunarity = 2;
    Distortion = 0.01;
    ImgSeed = 1234;
    ImgOctaves = 6;
    ImgPersistence = 0.5;
    ImgFrequency = 2;
    ImgQuality = 1;
    ImgScale = 0.025;
    ImgLacunarity = 2;
    ImgDistortion = 0.01;
}