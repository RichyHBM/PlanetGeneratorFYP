#ifdef GLFW

#include "WindowGLFW.hpp"
#include <GL/wglew.h>
#include "./Settings.hpp"
#include <iostream>

int WindowGLFW::mWindowCount = 0;
bool WindowGLFW::mGLFWInitialised = false;

WindowGLFW::WindowGLFW()
{
    mWindow = NULL;

    if( WindowGLFW::mWindowCount == 0
        && WindowGLFW::mGLFWInitialised == false ) {
        if( !glfwInit() ) {
            return;
        }

        WindowGLFW::mGLFWInitialised = true;
    }

    //Initialize local variables using settings
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
    glfwWindowHint( GLFW_SAMPLES, antiAliasing ); // Request 2 levels of antialiasing
    glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, majorOGL );
    glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, minorOGL );
    glfwWindowHint( GLFW_RESIZABLE, GL_FALSE );
    glfwWindowHint( GLFW_RED_BITS, 8 );
    glfwWindowHint( GLFW_GREEN_BITS, 8 );
    glfwWindowHint( GLFW_BLUE_BITS, 8 );
    glfwWindowHint( GLFW_ALPHA_BITS, 8 );
    glfwWindowHint( GLFW_DEPTH_BITS, depthBits );
    glfwWindowHint( GLFW_STENCIL_BITS,  stencilBits );
    glfwWindowHint ( GLFW_REFRESH_RATE, fps );

    if( vSynk ) {
        glfwSwapInterval( 1 );

    } else {
        glfwSwapInterval( 0 );
    }

    //Create the window using given parameters
    if( fullScreen ) {
        mWindow = glfwCreateWindow( width, height, title.c_str(), glfwGetPrimaryMonitor(), NULL );

    } else {
        mWindow = glfwCreateWindow( width, height, title.c_str(), NULL, NULL );
    }

    if ( !mWindow ) {
        mWindow = NULL;
        Log.Error( "GLFW could not open the window" );
        return;
    }

    glfwMakeContextCurrent( mWindow );
    GLenum err = glewInit();

    if ( GLEW_OK != err ) {
        // Problem: glewInit failed, something is seriously wrong.
        glfwDestroyWindow( mWindow );
        Log.Error( Util::ToString( glewGetErrorString( err ) ) );
        std::cin.get();
        return;
    }

    if( vSynk ) {
        glfwSwapInterval( 1 );

    } else {
        glfwSwapInterval( 0 );
    }

    Log.Info( "Using GLEW " + Util::ToString( glewGetString( GLEW_VERSION ) ) );
    //Retrieve GL version
    int glfwMajor = 0, glfwMinor = 0, glfwRev = 0;
    glfwGetVersion( &glfwMajor, &glfwMinor, &glfwRev );
    Log.Info( "Using OpenGL " + Util::ToString( glfwMajor ) + "." + Util::ToString( glfwMinor ) + "." + Util::ToString( glfwRev ) );
    //Enable GL features
    glEnable( GL_CULL_FACE );
    glEnable( GL_DEPTH_TEST );
    glEnable ( GL_BLEND );
    glBlendFunc ( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
    glFrontFace( GL_CCW );
    //Get running settings
    depthBits = glfwGetWindowAttrib( mWindow,  GLFW_DEPTH_BITS );
    stencilBits = glfwGetWindowAttrib( mWindow, GLFW_STENCIL_BITS );
    antiAliasing = glfwGetWindowAttrib( mWindow, GLFW_SAMPLES );
    majorOGL = glfwGetWindowAttrib( mWindow, GLFW_CONTEXT_VERSION_MAJOR );
    minorOGL = glfwGetWindowAttrib( mWindow, GLFW_CONTEXT_VERSION_MINOR );
    glfwGetWindowSize( mWindow, &width, &height );
    //Set the running settings
    Settings::Running.SetSettings( depthBits, stencilBits, antiAliasing, majorOGL, minorOGL, width, height, fps, vSynk, fullScreen );
    //glfwSetKeyCallback(KeyBoard::SetCallBack);
    WindowGLFW::mWindowCount++;
    mNeedsClose = false;
}

WindowGLFW::~WindowGLFW()
{
    //Close the window
    if( IsWindowCreated() ) {
        glfwDestroyWindow( mWindow );
        WindowGLFW::mWindowCount--;
    }

    //if no more windows are open, close down glfw
    if( WindowGLFW::mWindowCount == 0 && WindowGLFW::mGLFWInitialised ) {
        WindowGLFW::mGLFWInitialised = false;
        glfwTerminate();
    }
}

bool WindowGLFW::IsWindowCreated()
{
    return mWindow != NULL;
}

bool WindowGLFW::IsFocused()
{
    return glfwGetWindowAttrib( mWindow, GLFW_FOCUSED ) == GL_TRUE;
}

void WindowGLFW::MakeContextCurrent()
{
    glfwMakeContextCurrent( mWindow );
}

bool WindowGLFW::IsOpen()
{
    if( glfwWindowShouldClose( mWindow ) ) {
        mNeedsClose = true;
        return false;
    }

    return true;
}

GLFWwindow *WindowGLFW::GetGLFWWindow()
{
    return mWindow;
}

void WindowGLFW::SetCursor( CursorState pState )
{
    switch ( pState ) {
        case Hidden:
            glfwSetInputMode( mWindow, GLFW_CURSOR, GLFW_CURSOR_HIDDEN  );
            break;

        case Shown:
            glfwSetInputMode( mWindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL  );
            break;

        case Locked:
            glfwSetInputMode( mWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED  );
            break;

        default:
            break;
    }
}

void WindowGLFW::ResetDelta()
{
    //double delta = glfwGetTime();
    //if(delta < 0.0) delta = 0.0;
    //glfwSleep(upTime - delta);
    mDelta = glfwGetTime();
    glfwSetTime( 0.0 );
}

void WindowGLFW::Display()
{
    glfwSwapBuffers( mWindow );
}

void WindowGLFW::DoEvents()
{
    glfwPollEvents();
}

void WindowGLFW::Close()
{
    glfwSetWindowShouldClose( mWindow, GL_TRUE );

    //Not sure if terminatig the window here might bring bugs in the future
    if( IsWindowCreated() ) {
        glfwDestroyWindow( mWindow );
        mWindow = NULL;
        WindowGLFW::mWindowCount--;
    }
}

#endif