#include "RuntimeSettings.hpp"

#include <cstdlib>

RuntimeSettings RuntimeSettings::Settings;

RuntimeSettings::RuntimeSettings() 
{
    DrawLines = false;
    Subdivisions = 6;
    Distortions = 250;
    PlanetRadius = 100;
    LockMouse = true;
    Seed = rand() % 100000;
}