#include "framework/Includes.hpp"

#include "Program.hpp"
#include "framework/Window/WindowSettings.hpp"
#include "framework/RuntimeSettings.hpp"
#include "framework/Utilities.hpp"
#include "framework/Managers/MatrixManager.hpp"

#include "framework/Input/Mouse.hpp"

#include "TweakSetup.hpp"

Program::Program( Window *pWindow ) : mDebugInfo( pWindow )
{
    mWindow = pWindow;
    //Make sure the user starts far away enough to view the planet completelly
    MatrixControl.SetPosition( glm::vec3( 1, 1, RuntimeSettings::Settings.PlanetRadius * 5 ) );
    //Initialize tweakbar
    TwInit( TW_OPENGL, NULL );
    TwWindowSize( WindowSettings::Running.GetWidth(), WindowSettings::Running.GetHeight() );
    SetupTweakControls( this );
}

Program::~Program()
{
    TwTerminate();
    mWindow = NULL;
    //dtor
}

DrawDebugInfo *Program::GetDebugInfo()
{
    return &mDebugInfo;
}

RoundedCube *Program::GetRoundedCube()
{
    return &mRoundedCube;
}

Window *Program::GetWindow()
{
    return mWindow;
}

//Main program loop
void Program::Run()
{
    //Make sure the mouse starts in the right position to not capture erroneous movement
    Mouse::Set( WindowSettings::Running.GetWidth()/2.0f, WindowSettings::Running.GetHeight()/2.0f );

    while( !mWindow->NeedsToClose() ) {
        RuntimeSettings::PreviousFrame = RuntimeSettings::Settings;
        //Perform internal events
        mWindow->DoEvents();

        //show or hide the cursor if the window changes focus
        if( mWindow->IsFocused() ) {
            mWindow->MakeContextCurrent();
            mWindow->SetCursor( RuntimeSettings::Settings.LockMouse ? Hidden : Shown );

        } else {
            mWindow->SetCursor( Shown );
        }

        if( mWindow->IsFocused() ) {
            //break out of the loop when the user wants to close
            if( mWindow->NeedsToClose() ) {
                break;
            }

            Update();

            if( RuntimeSettings::Settings.LockMouse ) {
                Mouse::Set( WindowSettings::Running.GetWidth()/2.0f, WindowSettings::Running.GetHeight()/2.0f );
            }

            //Reset the frame time counter
            mWindow->ResetDelta();
            RuntimeSettings::Settings.Delta = mWindow->GetDelta();
            //Draw and check for errors
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

    if( !RuntimeSettings::Settings.FreezeFrustrum ) {
        mFrustrum.Update();
    }

    mRoundedCube.Update( mFrustrum );

    if( !RuntimeSettings::Settings.LockMouse ) {
        mDebugInfo.SetVertices( mRoundedCube.GetVertexCount() );
    }
}

void Program::Draw()
{
    //Create the matrices for OpenGL
    glm::mat4 model( 1.0f );
    glm::mat4 mMVP = MatrixControl.PerspectiveView() * model;
    //Clear the screen on every draw
    glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    //Can change to only draw lines if required
    if( RuntimeSettings::Settings.DrawLines ) {
        glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
    }

    mRoundedCube.Draw( mFrustrum );
    glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );

    if( RuntimeSettings::Settings.FreezeFrustrum ) {
        mFrustrum.Draw();
    }

    //Tweakbar uses old OGL drawing so make sure everything stays the same after drawing it
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
