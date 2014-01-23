#include "RuntimeSettings.hpp"

#include <cstdlib>

RuntimeSettings RuntimeSettings::Settings;

RuntimeSettings::RuntimeSettings()
{
    DrawLines = false;
    Subdivisions = 4;
    Distortions = 200;
    PlanetRadius = 100;
    LockMouse = true;
    Seed = rand() % 100000;
    FreezeFrustrum = false;
}