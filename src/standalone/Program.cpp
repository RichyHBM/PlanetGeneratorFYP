#include "framework/Includes.hpp"

#include "Program.hpp"
#include "framework/WindowSettings.hpp"
#include "framework/RuntimeSettings.hpp"
#include "framework/Utilities.hpp"
#include "framework/MatrixManager.hpp"

#include "framework/Input/Mouse.hpp"
#include <AntTweakBar.h>

Program::Program( Window *pWindow ) : mDebugInfo( pWindow )
{
    mWindow = pWindow;
    MatrixControl.SetPosition( glm::vec3( 1, 1, 50 ) );
    TwInit( TW_OPENGL, NULL );
    TwWindowSize( WindowSettings::Running.GetWidth(), WindowSettings::Running.GetHeight() );
    TwBar *myBar;
    myBar = TwNewBar( "Controls" );
    TwSetParam( myBar, NULL, "position", TW_PARAM_CSTRING, 1, "20 60" );
    TwAddVarRW( myBar, "DrawLines", TW_TYPE_BOOLCPP, &RuntimeSettings::Settings.DrawLines, NULL );
    TwAddVarRW( myBar, "Subdivisions", TW_TYPE_INT32, &RuntimeSettings::Settings.Subdivisions, NULL );
    TwAddVarRW( myBar, "Distortions", TW_TYPE_INT32, &RuntimeSettings::Settings.Distortions, NULL );
    TwAddVarRW( myBar, "PlanetRadius", TW_TYPE_FLOAT, &RuntimeSettings::Settings.PlanetRadius, NULL );
}

Program::~Program()
{
    TwTerminate();
    mWindow = NULL;
    //dtor
}

void Program::Run()
{
	Mouse::Set( WindowSettings::Running.GetWidth()/2.0f, WindowSettings::Running.GetHeight()/2.0f );
    while( !mWindow->NeedsToClose() ) {
        mWindow->DoEvents();

        if( mWindow->IsFocused() ) {
            mWindow->MakeContextCurrent();
            mWindow->SetCursor( RuntimeSettings::Settings.LockMouse ? Hidden : Shown );
        }

        if( !mWindow->IsFocused() ) {
            mWindow->SetCursor( Shown );
        }

        if( mWindow->IsFocused() ) {
            if( mWindow->NeedsToClose() ) {
                break;
            }

            Update();

            if( RuntimeSettings::Settings.LockMouse ) {
                Mouse::Set( WindowSettings::Running.GetWidth()/2.0f, WindowSettings::Running.GetHeight()/2.0f );
            }

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
    if( RuntimeSettings::Settings.LockMouse ) {
        Input::Manager.Update();
    }

    mIcosphere.Update();

    if( !RuntimeSettings::Settings.LockMouse ) {
        mDebugInfo.SetVertices( mIcosphere.GetVertexCount() );
    }
}

void Program::Draw()
{
    glm::mat4 model( 1.0f );
    glm::mat4 mMVP = MatrixControl.PerspectiveView() * model;
    glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    if( RuntimeSettings::Settings.DrawLines ) {
        glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
    }

    mIcosphere.Draw();
    glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );

    if( !RuntimeSettings::Settings.LockMouse ) {
        mDebugInfo.Draw();
        mWindow->SaveGLStates();
        TwDraw();
        mWindow->RestoreGLStates();
    }
}

const double Program::GetDelta()
{
    return mWindow->GetDelta();
}
