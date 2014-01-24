#include "RuntimeSettings.hpp"

#include <cstdlib>

RuntimeSettings RuntimeSettings::Settings;

RuntimeSettings::RuntimeSettings()
{
    DrawLines = false;
    Subdivisions = 1;
    Distortions = 0;
    PlanetRadius = 100;
    LockMouse = true;
    Seed = rand() % 100000;
    FreezeFrustrum = false;
}