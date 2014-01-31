#include "RuntimeSettings.hpp"

#include <cstdlib>

RuntimeSettings RuntimeSettings::Settings;
RuntimeSettings RuntimeSettings::PreviousFrame;

RuntimeSettings::RuntimeSettings()
{
    DrawLines = false;
    Subdivisions = 1;
    PlanetRadius = 100;
    LockMouse = true;
    FreezeFrustrum = false;
    DrawHidden = true;
    LightDirection = glm::vec3( 0,0,-1 );

    Seed = 1234;
    Octaves = 6;
    Persistence = 0.5;
    Frequency = 2;
    Quality = 1;
    Scale = 0.025;
    Lacunarity = 2;
    Distortion = 0.01;
}