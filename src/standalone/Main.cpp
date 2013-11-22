#include "framework/Includes.hpp"

#include "framework/Settings.hpp"
#include "framework/Utilities.hpp"
#include "./Program.hpp"
#include "framework/Window.hpp"

#include "framework/DebugOperators.hpp"
#include "framework/Noise/NoiseppNoise.hpp"
#include "framework/MatrixManager.hpp"

#ifdef SFML
#include "framework/WindowSFML.hpp"
#elif defined GLFW
#include "framework/WindowGLFW.hpp"
#endif

//Set initial settings
void SetSettings();
void ProcessArgument( const std::string &arg, const std::string &arg2 );

int main( int argc, const char *argv[] )
{
	SetSettings();
	MatrixControl.Init();

    NoisePP.ParseArguments( argc, argv );
    Settings::ParseArguments( argc, argv );
	NoisePP.SetSeed(54321);
	NoisePP.Init();

	Input::Manager.SetType(Input::KEYBOARD);

	for( int i = 0; i < argc; i++ ) {
		if(argc > i+1){
			ProcessArgument( argv[i], argv[i+1] );
		}
    }

#ifdef SFML
    Window *window = new( MemoryUse::Normal ) WindowSFML();
#elif defined GLFW
    Window *window = new( MemoryUse::Normal ) WindowGLFW();
#endif

    if( !window->IsWindowCreated() ) {
        Log.Error( "Failed to create window" );
        return -2;
    }

    //Create and run a new program instance
    Program *program = new( MemoryUse::Normal ) Program( window );
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
    width = 800,
    height = 600,
    fps = 60;
    bool vSynk = false, fullScreen = false;
    Settings::Initial.SetSettings( depthBits, stencilBits, antiAliasing, majorOGL, minorOGL, width, height, fps, vSynk, fullScreen );
}

void ProcessArgument( const std::string &arg, const std::string &arg2 )
{
	if( arg == "-viewDisp" ) {
		float displacement = Util::StrTo<float> (arg2);
        MatrixControl.SetDisplacement( displacement );
	}
}


