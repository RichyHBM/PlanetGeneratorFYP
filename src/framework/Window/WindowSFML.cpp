#ifdef SFML

#include "../Includes.hpp"
#include "WindowSFML.hpp"
#include <GL/glew.h>
#include "WindowSettings.hpp"
#include <iostream>
#include "../GLHelp/Texture.hpp"
#include "../Utilities.hpp"
#include "../TweakSFML.hpp"
#include "../RuntimeSettings.hpp"
#include "../Managers/MatrixManager.hpp"

WindowSFML::WindowSFML()
{
    //Initialize local variables using setings
    std::string title = "PlanetGenFYP";
    sf::ContextSettings contextSettings;
    contextSettings.depthBits = WindowSettings::Initial.GetDepthBits();
    contextSettings.stencilBits = WindowSettings::Initial.GetStencilBits();
    contextSettings.antialiasingLevel = WindowSettings::Initial.GetAntiAliasing();
    contextSettings.majorVersion = WindowSettings::Initial.GetMajorOGL();
    contextSettings.minorVersion = WindowSettings::Initial.GetMinorOGL();
    int fps = WindowSettings::Initial.GetFPS();
    int width = WindowSettings::Initial.GetWidth(),
        height = WindowSettings::Initial.GetHeight();
    bool vSynk = WindowSettings::Initial.GetVSynk(), fullScreen = WindowSettings::Initial.GetFullScreen();
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
    WindowSettings::Running.SetSettings( depthBits, stencilBits, antiAliasing, majorOGL, minorOGL, width, height, fps, vSynk, fullScreen, WindowSettings::Initial.UseTweakBar() );
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
        if( WindowSettings::Running.UseTweakBar() ) {
            if( TweakEventSFML( event ) != 0 ) {
                continue;
            }
        }

        if ( event.type == sf::Event::Closed ) {
            mNeedsClose = true;

        } else if ( event.type == sf::Event::Resized ) {
            // adjust the viewport when the window is resized
            glViewport( 0, 0, event.size.width, event.size.height );
            WindowSettings::Running.SetResolution( event.size.width, event.size.height );
            MatrixControl.SetWidthHeight( event.size.width, event.size.height );

        } else if( event.type == sf::Event::GainedFocus ) {
            mIsFocused = true;

        } else if( event.type == sf::Event::LostFocus ) {
            mIsFocused = false;

        } else if( event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::F4 ) {
            Texture::Screenshot( "Screenshot.bmp", 0, 0, WindowSettings::Running.GetWidth(), WindowSettings::Running.GetHeight() );

        } else if( event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape ) {
            RuntimeSettings::Settings.LockMouse = !RuntimeSettings::Settings.LockMouse;
            sf::Mouse::setPosition( sf::Vector2i( WindowSettings::Running.GetWidth()/2.0f, WindowSettings::Running.GetHeight()/2.0f ) );
            mWindow.setMouseCursorVisible( RuntimeSettings::Settings.LockMouse );
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
    mNeedsClose = true;
}

#endif //SFML
