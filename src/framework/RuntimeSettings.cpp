#include "RuntimeSettings.hpp"

#include <cstdlib>

RuntimeSettings RuntimeSettings::Settings;
RuntimeSettings RuntimeSettings::PreviousFrame;

RuntimeSettings::RuntimeSettings()
{
    DrawLines = false;
    Subdivisions = 7;
    PlanetRadius = 200;
    WaterRadius = 200;
    LockMouse = true;
    FreezeFrustrum = false;
    DrawHidden = true;
    LightDirection = glm::vec3( 0,0,-1 );
    WaterColor = glm::vec4( 0.211, 0.713, 1, 0.5 );
    RealtimeRebuild = false;
    Seed = 1234;
    Octaves = 6;
    Persistence = 0.5;
    Frequency = 2;
    Quality = 1;
    Scale = 0.05;
    Lacunarity = 2;
    Distortion = 0.005;
    GrassHeight = ( PlanetRadius*2 ) + 1;
    DirtHeight = ( PlanetRadius*2 ) + 3;
    SnowHeight = ( PlanetRadius*2 ) + 7;
    WaveSize = 0.00002f;
    SinAmount = 0.00001f;
}