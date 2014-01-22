#ifndef RUNTIMESETTINGS_HPP
#define RUNTIMESETTINGS_HPP

#include <string>

class RuntimeSettings
{
public:
    //Startup settings
    static RuntimeSettings Settings;

    RuntimeSettings();

    bool DrawLines;
    unsigned int Subdivisions;
    unsigned int Distortions;
    unsigned int PlanetRadius;
    bool LockMouse;
};

#endif // RUNTIMESETTINGS_HPP
