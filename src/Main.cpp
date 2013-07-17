#include "Includes.hpp"

#include "./Settings.hpp"

///
///Set initial settings
///
void SetSettings();

int main(int argc, const char* argv[])
{
    if( !glfwInit() )
    {
        return -1;
    }

    SetSettings();

    //Initialize local variables using setings
    std::string title = "PlanetGenFYP";
    unsigned short
    depthBits = Settings::Initial.GetDepthBits(),
    stencilBits = Settings::Initial.GetStencilBits(),
    antiAliasing = Settings::Initial.GetAntiAliasing(),
    majorOGL = Settings::Initial.GetMajorOGL(),
    minorOGL = Settings::Initial.GetMinorOGL(),
    fps = Settings::Initial.GetFPS();

    int width = Settings::Initial.GetWidth(),
        height = Settings::Initial.GetHeight();

    bool vSynk = Settings::Initial.GetVSynk(), fullScreen = Settings::Initial.GetFullScreen();

    //Set window parameters
    glfwOpenWindowHint(GLFW_FSAA_SAMPLES, antiAliasing);  // Request 2 levels of antialiasing
    glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, majorOGL);
    glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, minorOGL);
    glfwOpenWindowHint(GLFW_WINDOW_NO_RESIZE, GL_TRUE);

    //Create the window using given parameters
    int winSuccess = 0;
    if(fullScreen)
        winSuccess = glfwOpenWindow( width, height, 8, 8, 8, 8, depthBits, stencilBits, GLFW_FULLSCREEN );
    else
        winSuccess = glfwOpenWindow( width, height, 8, 8, 8, 8, depthBits, stencilBits, GLFW_WINDOW );
    if(winSuccess == GL_FALSE) return -1;

    glfwSetWindowTitle("PlanetGenFYP");

    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
        // Problem: glewInit failed, something is seriously wrong.
        std::cout << "Error: " << glewGetErrorString(err) << std::endl;
        return 32;
    }
    std::cout << "Using GLEW " << glewGetString(GLEW_VERSION) << std::endl;
    //Retrieve GL version
    int glfwMajor = 0, glfwMinor = 0, glfwRev = 0;
    glfwGetVersion( &glfwMajor, &glfwMinor, &glfwRev );

    std::cout << "Using GLFW " << glfwMajor << "." << glfwMinor << "." << glfwRev << std::endl;

    //Enable GL features
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    glEnable (GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glFrontFace(GL_CCW);

    //Get running settings
    depthBits = glfwGetWindowParam(GLFW_DEPTH_BITS);
    stencilBits = glfwGetWindowParam(GLFW_STENCIL_BITS);
    antiAliasing = glfwGetWindowParam(GLFW_FSAA_SAMPLES);
    majorOGL = glfwGetWindowParam(GLFW_OPENGL_VERSION_MAJOR);
    minorOGL = glfwGetWindowParam(GLFW_OPENGL_VERSION_MINOR);

    glfwGetWindowSize( &width, &height );

    //Set the running settings 
    Settings::Running.SetSettings(depthBits, stencilBits, antiAliasing, majorOGL, minorOGL, width, height, fps, vSynk, fullScreen);

    //glfwSetKeyCallback(KeyBoard::SetCallBack);

    //Create and run a new game instance
    Game *game = new Game();
    game->Run();
    delete game;

    glfwTerminate();


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

    bool vSynk = false, fullScreen = false;

    Settings::Initial.SetSettings(depthBits, stencilBits, antiAliasing, majorOGL, minorOGL, width, height, fps, vSynk, fullScreen);

}

