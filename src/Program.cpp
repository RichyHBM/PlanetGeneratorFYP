#include "Includes.hpp"

#include "Program.hpp"

#include "./Keyboard.hpp"
#include "./Settings.hpp"
#include "./Utilities.hpp"

#include <GLFW/glfw3.h>

Program::Program( Window &pWindow ) : mWindow( pWindow )
{
    mBT.LoadFile( "./Resources/cBitmap.png", "./Resources/cInfo.h.txt" );
    mBT.SetPosition( glm::vec2( 10,5 ) );
    mBT.SetColor( 1.0f , 1.0f, 1.0f , 1.0f );
    mBT.SetText( "Hello" );
}

Program::~Program()
{
    //dtor
}

void Program::Run()
{
    while( mWindow.IsOpen() ) {
        KeyBoard::keyboard.Update( mWindow.GetGLFWWindow() );

        if( KeyBoard::keyboard.HasKeyBeenPressed( GLFW_KEY_ESCAPE ) ) {
            mWindow.Close();
        }

        if( mWindow.IsFocused() ) {
            mWindow.MakeContextCurrent();
            mWindow.SetCursor( CursorState::Hidden );
        }

        if( !mWindow.IsFocused() ) {
            mWindow.SetCursor( CursorState::Shown );
        }

        if( mWindow.IsFocused() ) {
            HandleEvents();
        }

        if( mWindow.IsFocused() ) {
            if( !mWindow.IsOpen() ) {
                break;
            }

            Update();
            Draw();
            mWindow.SwapBuffersAndPollEvents();
            Util::PrintGLErrors();

        } else {
            mWindow.SwapBuffersAndPollEvents();
        }
    }
}

void Program::HandleEvents()
{
}

void Program::Update()
{
}

void Program::Draw()
{
    glClearColor( 1.0f, 0.0f, 0.0f, 1.0f );
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    mBT.Draw();
}

const double Program::GetDelta()
{
    return mDelta;
}