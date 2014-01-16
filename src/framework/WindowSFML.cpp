#ifdef SFML

#include "Includes.hpp"
#include "WindowSFML.hpp"
#include <GL/glew.h>
#include "./Settings.hpp"
#include <iostream>
#include "GLHelp/Texture.hpp"
#include "Utilities.hpp"

WindowSFML::WindowSFML()
{
    //Initialize local variables using setings
    std::string title = "PlanetGenFYP";
    sf::ContextSettings contextSettings;
    contextSettings.depthBits = Settings::Initial.GetDepthBits();
    contextSettings.stencilBits = Settings::Initial.GetStencilBits();
    contextSettings.antialiasingLevel = Settings::Initial.GetAntiAliasing();
    contextSettings.majorVersion = Settings::Initial.GetMajorOGL();
    contextSettings.minorVersion = Settings::Initial.GetMinorOGL();
    int fps = Settings::Initial.GetFPS();
    int width = Settings::Initial.GetWidth(),
        height = Settings::Initial.GetHeight();
    bool vSynk = Settings::Initial.GetVSynk(), fullScreen = Settings::Initial.GetFullScreen();
    //Create the window using given parameters
    int bitsPerPixel = contextSettings.depthBits + contextSettings.stencilBits;

    if( fullScreen ) {
        mWindow.create( sf::VideoMode( width, height, bitsPerPixel ), title, sf::Style::Fullscreen, contextSettings );

    } else {
        mWindow.create( sf::VideoMode( width, height, bitsPerPixel ), title, sf::Style::Titlebar | sf::Style::Close, contextSettings );
    }

    if ( !mWindow.isOpen() ) {
        return;
    }

    mWindow.setActive( true );
    GLenum err = glewInit();

    if ( GLEW_OK != err ) {
        // Problem: glewInit failed, something is seriously wrong.
        mWindow.close();
        Log.Error( Util::ToString( glewGetErrorString( err ) ) );
        return;
    }

    if( vSynk ) {
        mWindow.setVerticalSyncEnabled( true );
        mWindow.setFramerateLimit( fps );

    } else {
        mWindow.setVerticalSyncEnabled( false );
        mWindow.setFramerateLimit( fps );
    }

    Log.Info( "Using GLEW " + Util::ToString( glewGetString( GLEW_VERSION ) ) );
    //Retrieve GL version
    sf::ContextSettings runtimeContextSettings;
    runtimeContextSettings = mWindow.getSettings();
    Log.Info( "Using OpenGL " + Util::ToString( runtimeContextSettings.majorVersion ) + "." + Util::ToString( runtimeContextSettings.minorVersion ) );
    Util::PrintGLErrors();
    //Enable GL features
    glEnable( GL_CULL_FACE );
    Util::PrintGLErrors();
    glEnable( GL_DEPTH_TEST );
    Util::PrintGLErrors();
    glEnable ( GL_BLEND );
    Util::PrintGLErrors();
    glBlendFunc ( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
    Util::PrintGLErrors();
    glFrontFace( GL_CCW );
    Util::PrintGLErrors();
    //Get running settings
    int depthBits =runtimeContextSettings.depthBits;
    int stencilBits = runtimeContextSettings.stencilBits;
    int antiAliasing = runtimeContextSettings.antialiasingLevel;
    int majorOGL = runtimeContextSettings.majorVersion;
    int minorOGL = runtimeContextSettings.minorVersion;
    width = mWindow.getSize().x;
    height = mWindow.getSize().y;
    //Set the running settings
    Settings::Running.SetSettings( depthBits, stencilBits, antiAliasing, majorOGL, minorOGL, width, height, fps, vSynk, fullScreen );
    mIsFocused = true;
    mNeedsClose = false;
}

WindowSFML::~WindowSFML()
{
}

void WindowSFML::DoEvents()
{
    sf::Event event;

    while ( mWindow.pollEvent( event ) ) {
        if ( event.type == sf::Event::Closed ) {
            mNeedsClose = true;

        } else if ( event.type == sf::Event::Resized ) {
            // adjust the viewport when the window is resized
            glViewport( 0, 0, event.size.width, event.size.height );

        } else if( event.type == sf::Event::GainedFocus ) {
            mIsFocused = true;

        } else if( event.type == sf::Event::LostFocus ) {
            mIsFocused = false;

        } else if( event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::F4 ) {
            Texture::Screenshot( "Screenshot.bmp", 0, 0, Settings::Running.GetWidth(), Settings::Running.GetHeight() );

        } else if( event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape ) {
            mNeedsClose = true;
        }
    }
}

bool WindowSFML::IsFocused()
{
    return mIsFocused;
}

bool WindowSFML::IsOpen()
{
    return mWindow.isOpen();
}

void WindowSFML::SetCursor( CursorState pState )
{
    switch( pState ) {
        case Hidden:
            mWindow.setMouseCursorVisible( false );
            break;
        case Shown:
            mWindow.setMouseCursorVisible( true );
            break;
        case Locked:
            break;
    }
}

void WindowSFML::Display()
{
    mWindow.display();
}

bool WindowSFML::IsWindowCreated()
{
    return mWindow.isOpen();
}

void WindowSFML::MakeContextCurrent()
{
    mWindow.setActive( true );
}

void WindowSFML::ResetDelta()
{
    mDelta = mDeltaClock.restart().asSeconds();
}

void WindowSFML::Close()
{
    mWindow.close();
}

#endif //SFML