#ifndef RUNTIMESETTINGS_HPP
#define RUNTIMESETTINGS_HPP

#include <string>

class RuntimeSettings
{
public:
    //Startup settings
    static RuntimeSettings Settings;

    RuntimeSettings()
    {
        DrawLines = false;
    }

    bool DrawLines;

};

#endif // RUNTIMESETTINGS_HPP
