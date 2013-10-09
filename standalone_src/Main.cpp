#include "../src/Includes.hpp"

#include "../src/Settings.hpp"
#include "../src/Utilities.hpp"
#include "./Program.hpp"
#include "../src/Window.hpp"

#ifdef SFML
#include "../src/WindowSFML.hpp"
#elif defined GLFW
#include "../src/WindowGLFW.hpp"
#endif

#define OUTPUTTOCOUT

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

#ifndef OUTPUTTOCOUT
    std::streambuf *psbuf, *backup;
    std::ofstream filestr;
    filestr.open( Util::GetLocalDateTime( "PlanetGen_log_%Y-%m-%d_%H-%M-%S.txt" ).c_str() );
    backup = std::cout.rdbuf();     // back up cout's streambuf
    psbuf = filestr.rdbuf();   // get file's streambuf
    std::cout.rdbuf( psbuf );
#endif
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
    Program *program = new Program( window );
    program->Run();
    delete program;
    delete window;
#ifndef OUTPUTTOCOUT
    std::cout.rdbuf( backup );      // restore cout's original streambuf
    filestr.close();
#endif
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
    width = 1240,
    height = 720,
    fps = 60;
    bool vSynk = false, fullScreen = false;
    Settings::Initial.SetSettings( depthBits, stencilBits, antiAliasing, majorOGL, minorOGL, width, height, fps, vSynk, fullScreen );
}

void ProcessArgument( const std::string &arg )
{
}
