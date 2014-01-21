#include "framework/Includes.hpp"

#include "Program.hpp"
#include "framework/WindowSettings.hpp"
#include "framework/RuntimeSettings.hpp"
#include "framework/Utilities.hpp"
#include "framework/MatrixManager.hpp"

#include "framework/Input/Mouse.hpp"

Program::Program( Window *pWindow ) : mDebugInfo( pWindow )
{
    mWindow = pWindow;
    MatrixControl.SetPosition( glm::vec3( 1, 1, 50 ) );
}

Program::~Program()
{
    mWindow = NULL;
    //dtor
}

void Program::Run()
{
    while( !mWindow->NeedsToClose() ) {
        mWindow->DoEvents();

        if( mWindow->IsFocused() ) {
            mWindow->MakeContextCurrent();
            mWindow->SetCursor( Hidden );
        }

        if( !mWindow->IsFocused() ) {
            mWindow->SetCursor( Shown );
        }

        if( mWindow->IsFocused() ) {
            if( mWindow->NeedsToClose() ) {
                break;
            }

            Update();
            Mouse::Set( WindowSettings::Running.GetWidth()/2.0f, WindowSettings::Running.GetHeight()/2.0f );
            mWindow->ResetDelta();
            Draw();
            mWindow->Display();
            Util::PrintGLErrors();

        } else {
            mWindow->Display();
        }
    }
}

void Program::Update()
{
    Input::Manager.Update();

    if( sf::Keyboard::isKeyPressed( sf::Keyboard::F10 ) ) {
        mDebugInfo.SetDraw( true );
    }

    if( sf::Keyboard::isKeyPressed( sf::Keyboard::F11 ) ) {
        mDebugInfo.SetDraw( false );
    }

    if( sf::Keyboard::isKeyPressed( sf::Keyboard::F5 ) ) {
        RuntimeSettings::Settings.DrawLines = true;
    }else{
        RuntimeSettings::Settings.DrawLines = false;
    }


    mIcosphere.Update();
}

void Program::Draw()
{
    glm::mat4 model( 1.0f );
    glm::mat4 mMVP = MatrixControl.PerspectiveView() * model;
    glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    if(RuntimeSettings::Settings.DrawLines)
        glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
    mIcosphere.Draw();
    glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
    mDebugInfo.Draw();
}

const double Program::GetDelta()
{
    return mWindow->GetDelta();
}
