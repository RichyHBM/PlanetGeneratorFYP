#include "RuntimeSettings.hpp"

RuntimeSettings RuntimeSettings::Settings;

RuntimeSettings::RuntimeSettings() 
{
    DrawLines = false;
    Subdivisions = 6;
    Distortions = 250;
    PlanetRadius = 100;
    LockMouse = true;
}