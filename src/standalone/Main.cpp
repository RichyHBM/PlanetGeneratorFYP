#include <cstdlib>

#include "framework/Includes.hpp"

#include "framework/Window/WindowSettings.hpp"
#include "framework/Utilities.hpp"
#include "framework/RuntimeSettings.hpp"
#include "./Program.hpp"
#include "framework/Window/Window.hpp"

#include "framework/Debugs/DebugOperators.hpp"
#include "framework/Noise/NoiseppNoise.hpp"
#include "framework/Managers/MatrixManager.hpp"
#include "framework/Managers/ResourceManager.hpp"

#include "framework/Window/WindowSFML.hpp"

//Set initial settings
void SetSettings();
void ProcessArgument( const std::string &arg, const std::string &arg2 );

int main( int argc, const char *argv[] )
{
    SetSettings();
    MatrixControl.Init();

    for( int i = 0; i < argc; i++ ) {
        if( argc > i+1 ) {
            ProcessArgument( argv[i], argv[i+1] );
            WindowSettings::ParseArguments( argv[i], argv[i+1] );
        }
    }
    //Pass an enum to the new keyword to allow keeping track of memory
    Window *window = new( MemoryUse::Normal ) WindowSFML();

    if( !window->IsWindowCreated() ) {
        Log.Error( "Failed to create window" );
        return -2;
    }

    //Create and run a new program instance
    Program *program = new( MemoryUse::Normal ) Program( window );
    program->Run();
    //Delete all allocated memory
    delete program;
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
    antiAliasing = 2,
    majorOGL = 2,
    minorOGL = 1,
    width = 800,
    height = 600,
    fps = 60;
    bool vSynk = false, fullScreen = false, useTweakBar = true;
    WindowSettings::Initial.SetSettings( depthBits, stencilBits, antiAliasing, majorOGL, minorOGL, width, height, fps, vSynk, fullScreen, useTweakBar );
}

void ProcessArgument( const std::string &arg, const std::string &arg2 )
{
    if( arg == "-controls" ) {
        if( Util::StrTo<int> ( arg2 ) == 0 ) {
            Input::Manager.SetType( Input::KEYBOARD );

        } else if( Util::StrTo<int> ( arg2 ) == 1 ) {
            Input::Manager.SetType( Input::GAMEPAD );
        }
    }
}


