#include "framework/Includes.hpp"

#include "Program.hpp"
#include "framework/Window/WindowSettings.hpp"
#include "framework/RuntimeSettings.hpp"
#include "framework/Utilities.hpp"
#include "framework/Managers/MatrixManager.hpp"

#include "framework/Input/Mouse.hpp"


void TW_CALL Program::QuitButton( void *clientData )
{
    ( ( Window * )clientData )->Close();
}

void TW_CALL Program::RebuildButton( void *clientData )
{
    ( ( Program * )clientData )->GetDebugInfo()->SetDrawRebuild();
    ( ( Program * )clientData )->Draw();
    ( ( Program * )clientData )->GetWindow()->Display();
    ( ( Program * )clientData )->GetRoundedCube()->RebuildNoise();
    ( ( Program * )clientData )->GetRoundedCube()->RebuildSides();
}


void TW_CALL Program::GetLightDirection( void *value, void *clientData )
{
}

void TW_CALL Program::SetLightDirection( const void *value, void *clientData )
{
}


Program::Program( Window *pWindow ) : mDebugInfo( pWindow )
{
    mWindow = pWindow;
    MatrixControl.SetPosition( glm::vec3( 1, 1, RuntimeSettings::Settings.PlanetRadius * 5 ) );
    TwInit( TW_OPENGL, NULL );
    TwWindowSize( WindowSettings::Running.GetWidth(), WindowSettings::Running.GetHeight() );
    TwBar *myBar;
    myBar = TwNewBar( "Controls" );
    TwSetParam( myBar, NULL, "position", TW_PARAM_CSTRING, 1, "20 60" );
    TwDefine( " Controls size='200 500' " );
    TwAddVarRW( myBar, "Draw Lines", TW_TYPE_BOOLCPP, &RuntimeSettings::Settings.DrawLines, NULL );
    TwAddVarRW( myBar, "Draw Hidden", TW_TYPE_BOOLCPP, &RuntimeSettings::Settings.DrawHidden, NULL );
    TwAddVarRW( myBar, "Freeze Frustrum", TW_TYPE_BOOLCPP, &RuntimeSettings::Settings.FreezeFrustrum, NULL );
    TwAddSeparator( myBar, NULL, NULL );
    TwAddVarRW( myBar, "Subdivisions", TW_TYPE_UINT32, &RuntimeSettings::Settings.Subdivisions, " max=8 " );
    TwAddVarRW( myBar, "Planet Radius", TW_TYPE_UINT32, &RuntimeSettings::Settings.PlanetRadius, NULL );
    TwAddSeparator( myBar, NULL, NULL );
    TwAddVarRW( myBar, "Light Direction", TW_TYPE_DIR3F, &RuntimeSettings::Settings.LightDirection, NULL );
    TwAddSeparator( myBar, NULL, NULL );
    TwAddVarRW( myBar, "Noise Seed", TW_TYPE_UINT32, &RuntimeSettings::Settings.Seed, NULL );
    TwAddVarRW( myBar, "Noise Octaves", TW_TYPE_UINT32, &RuntimeSettings::Settings.Octaves, NULL );
    TwAddVarRW( myBar, "Noise Persistence", TW_TYPE_DOUBLE, &RuntimeSettings::Settings.Persistence, NULL );
    TwAddVarRW( myBar, "Noise Frequency", TW_TYPE_DOUBLE, &RuntimeSettings::Settings.Frequency, NULL );
    TwAddVarRW( myBar, "Noise Quality", TW_TYPE_UINT32, &RuntimeSettings::Settings.Quality, NULL );
    TwAddVarRW( myBar, "Noise Scale", TW_TYPE_DOUBLE, &RuntimeSettings::Settings.Scale, NULL );
    TwAddVarRW( myBar, "Noise Lacunarity", TW_TYPE_DOUBLE, &RuntimeSettings::Settings.Lacunarity, NULL );
    TwAddVarRW( myBar, "Noise Distortion", TW_TYPE_DOUBLE, &RuntimeSettings::Settings.Distortion, NULL );
    TwAddSeparator( myBar, NULL, NULL );
    TwAddButton( myBar, "Rebuild", Program::RebuildButton, this, NULL );
    TwAddButton( myBar, "Quit", Program::QuitButton, mWindow, NULL );
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

void Program::Run()
{
    Mouse::Set( WindowSettings::Running.GetWidth()/2.0f, WindowSettings::Running.GetHeight()/2.0f );

    while( !mWindow->NeedsToClose() ) {
        RuntimeSettings::PreviousFrame = RuntimeSettings::Settings;
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
    glm::mat4 model( 1.0f );
    glm::mat4 mMVP = MatrixControl.PerspectiveView() * model;
    glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    if( RuntimeSettings::Settings.DrawLines ) {
        glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
    }

    mRoundedCube.Draw( mFrustrum );
    glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );

    if( RuntimeSettings::Settings.FreezeFrustrum ) {
        mFrustrum.Draw();
    }

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
