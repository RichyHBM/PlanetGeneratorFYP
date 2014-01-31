#include <cstdlib>

#include "framework/Includes.hpp"

#include "framework/Window/WindowSettings.hpp"
#include "framework/Utilities.hpp"
#include "framework/RuntimeSettings.hpp"
//#include "./Program.hpp"
#include "framework/Window/Window.hpp"

#include "framework/Debugs/DebugOperators.hpp"
#include "framework/Noise/NoiseppNoise.hpp"
#include "framework/Managers/MatrixManager.hpp"
#include "framework/Managers/ResourceManager.hpp"

#include "framework/Window/WindowSFML.hpp"

//Set initial settings
void SetSettings();

int main( int argc, const char *argv[] )
{
    SetSettings();
    MatrixControl.Init();

    for( int i = 0; i < argc; i++ ) {
        if( argc > i+1 ) {
            WindowSettings::ParseArguments( argv[i], argv[i+1] );
        }
    }

    Input::Manager.SetType( Input::NETWORK );
    Window *window = new( MemoryUse::Normal ) WindowSFML();

    if( !window->IsWindowCreated() ) {
        Log.Error( "Failed to create window" );
        return -2;
    }

    //Create and run a new program instance
    //Program *program = new( MemoryUse::Normal ) Program( window );
    //program->Run();
    //delete program;
    ResourceManager::Destroy();
    window->Close();
    delete window;
    //*/
    return 0;
}

void SetSettings()
{
    unsigned short
    depthBits = 24,
    stencilBits = 8,
    antiAliasing = 8,
    majorOGL = 2,
    minorOGL = 1,
    width = 4096,
    height = 2400,
    fps = 60;
    bool vSynk = false, fullScreen = true, useTweakBar = false;
    WindowSettings::Initial.SetSettings( depthBits, stencilBits, antiAliasing, majorOGL, minorOGL, width, height, fps, vSynk, fullScreen, useTweakBar );
}
