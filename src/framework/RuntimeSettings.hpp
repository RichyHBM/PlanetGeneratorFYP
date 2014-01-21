#ifndef RUNTIMESETTINGS_HPP
#define RUNTIMESETTINGS_HPP

#include <string>

class RuntimeSettings
{
public:
    //Startup settings
    static RuntimeSettings Settings;

    RuntimeSettings() {
        DrawLines = false;
        Subdivisions = 5;
        Distortions = 200;
        PlanetRadius = 5.0f;
        LockMouse = true;
    }

    bool DrawLines;
    int Subdivisions;
    int Distortions;
    float PlanetRadius;
    float LockMouse;
};

#endif // RUNTIMESETTINGS_HPP
