#ifndef WINDOWINIT_HPP
#define WINDOWINIT_HPP

#include "Includes.hpp"
#include "./Settings.hpp"
#include "./Utilities.hpp"

GLFWwindow *InitializeGLFW()
{
    if( !glfwInit() )
    {
        return NULL;
    }

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

	GLFWwindow* window;
    //Set window parameters
    glfwWindowHint( GLFW_SAMPLES, antiAliasing);  // Request 2 levels of antialiasing
    glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, majorOGL);
    glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, minorOGL);
    glfwWindowHint( GLFW_RESIZABLE, GL_FALSE);
	glfwWindowHint(GLFW_RED_BITS, 8);
	glfwWindowHint(GLFW_GREEN_BITS, 8);
	glfwWindowHint(GLFW_BLUE_BITS, 8);
	glfwWindowHint(GLFW_ALPHA_BITS, 8);
	glfwWindowHint(GLFW_DEPTH_BITS, depthBits);
	glfwWindowHint(GLFW_STENCIL_BITS,  stencilBits);
	glfwWindowHint (GLFW_REFRESH_RATE, fps);
	if(vSynk){
		glfwSwapInterval(1);
	}else{
		glfwSwapInterval(0);
	}
    //Create the window using given parameters
    if(fullScreen)
    {
       window = glfwCreateWindow(width, height, title.c_str(), glfwGetPrimaryMonitor(), NULL);
    }
    else
    {
       window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
    }
    if (!window)
    {
        glfwTerminate();
        return NULL;
    }
	glfwMakeContextCurrent(window);

    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
        // Problem: glewInit failed, something is seriously wrong.
        std::cout << "Error: " << glewGetErrorString(err) << std::endl;
		std::cin.get();
        return NULL;
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
    depthBits = glfwGetWindowAttrib( window,  GLFW_DEPTH_BITS);
    stencilBits = glfwGetWindowAttrib(window, GLFW_STENCIL_BITS);
    antiAliasing = glfwGetWindowAttrib(window, GLFW_SAMPLES);
    majorOGL = glfwGetWindowAttrib(window, GLFW_CONTEXT_VERSION_MAJOR);
    minorOGL = glfwGetWindowAttrib(window, GLFW_CONTEXT_VERSION_MINOR);

    glfwGetWindowSize( window, &width, &height );

    //Set the running settings
    Settings::Running.SetSettings(depthBits, stencilBits, antiAliasing, majorOGL, minorOGL, width, height, fps, vSynk, fullScreen);

    //glfwSetKeyCallback(KeyBoard::SetCallBack);
    return window;
}

#endif // WINDOWINIT_HPP
