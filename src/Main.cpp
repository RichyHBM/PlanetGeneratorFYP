#include "Includes.hpp"

#include "./Settings.hpp"
#include "./Utilities.hpp"
#include "./Program.hpp"
#include "./Window.hpp"
//#define OUTPUTTOCOUT

///
///Set initial settings
///
void SetSettings();
void ProcessArgument(const std::string &arg);

int main(int argc, const char* argv[])
{

	for(int i = 0; i < argc; i++){
		ProcessArgument(argv[i]);
	}


#ifndef OUTPUTTOCOUT
    std::streambuf *psbuf, *backup;
    std::ofstream filestr;
	filestr.open( Util::GetLocalDateTime("PlanetGen_log_%Y-%m-%d_%H-%M-%S.txt").c_str());
    backup = std::cout.rdbuf();     // back up cout's streambuf
    psbuf = filestr.rdbuf();   // get file's streambuf
    std::cout.rdbuf(psbuf);
#endif

	SetSettings();


	Window window;

	if(window.GetGLFWWindow() == NULL){
        return -2;
    }

    //Create and run a new program instance
	Program *program = new Program(window);
    program->Run();
    delete program;

#ifndef OUTPUTTOCOUT
    std::cout.rdbuf(backup);        // restore cout's original streambuf
    filestr.close();
#endif
	//*/
	std::cout << "Please press any key to exit" << std::endl;
	std::cin.get();
    return 0;
}

void SetSettings()
{
    unsigned short
    depthBits = 24,
    stencilBits = 8,
    antiAliasing = 4,
    majorOGL = 2,
    minorOGL = 0,
    width = 800,
    height = 600,
    fps = 60;

    bool vSynk = true, fullScreen = false;

    Settings::Initial.SetSettings(depthBits, stencilBits, antiAliasing, majorOGL, minorOGL, width, height, fps, vSynk, fullScreen);

}

void ProcessArgument(const std::string &arg)
{

}
