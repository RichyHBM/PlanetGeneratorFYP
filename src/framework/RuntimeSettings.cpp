#include "RuntimeSettings.hpp"

#include <cstdlib>

RuntimeSettings RuntimeSettings::Settings;
RuntimeSettings RuntimeSettings::PreviousFrame;

RuntimeSettings::RuntimeSettings()
{
    DrawLines = false;
    Subdivisions = 1;
    Distortions = 0;
    PlanetRadius = 100;
    LockMouse = true;
    Seed = rand() % 100000;
    FreezeFrustrum = false;
    DistortionSize = 1.0f;
    RealtimeRebuild = false;
    DrawHidden = true;
    LightDirection = glm::vec3( 0,0,-1 );
}