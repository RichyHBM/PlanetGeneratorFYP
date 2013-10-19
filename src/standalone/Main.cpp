#include "framework/Includes.hpp"

#include "framework/Settings.hpp"
#include "framework/Utilities.hpp"
#include "./Program.hpp"
#include "framework/Window.hpp"

#include "framework/DebugOperators.hpp"

#ifdef SFML
#include "framework/WindowSFML.hpp"
#elif defined GLFW
#include "framework/WindowGLFW.hpp"
#endif

///
///Set initial settings
///
void SetSettings();
void ProcessArgument( const std::string &arg );



int main( int argc, const char *argv[] )
{

    for( int i = 0; i < argc; i++ ) {
        ProcessArgument( argv[i] );
    }

    SetSettings();
#ifdef SFML
    Window *window = new WindowSFML();
#elif defined GLFW
    Window *window = new WindowGLFW();
#endif

    if( !window->IsWindowCreated() ) {
        return -2;
    }

    //Create and run a new program instance
    Program *program = new(MemoryUse::Normal) Program( window );
    program->Run();
    delete program;
    window->Close();
    delete window;
    
    //*/
    std::cin.get();
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
    width = 1280,
    height = 720,
    fps = 60;
    bool vSynk = false, fullScreen = false;
    Settings::Initial.SetSettings( depthBits, stencilBits, antiAliasing, majorOGL, minorOGL, width, height, fps, vSynk, fullScreen );
}

void ProcessArgument( const std::string &arg )
{
}
