#include "framework/Includes.hpp"

#include "Program.hpp"
#include "framework/Settings.hpp"
#include "framework/Utilities.hpp"
#include "framework/MatrixManager.hpp"

#include "framework/Input/Mouse.hpp"

#define PLANESIZE 100

Program::Program( Window *pWindow ) : mDebugInfo( pWindow )
{
    mWindow = pWindow;

    mShader.LoadShaderFiles( "./Resources/Terrain.vert" ,"./Resources/Terrain.frag" );

    for( int y = 0; y < PLANESIZE; y++ ) {
        for( int x = 0; x < PLANESIZE; x++ ) {
            glm::vec3 p1( x, NoisePP.Generate( x, y ) * 50, y );
            mVertexList.push_back( p1 );

            if( p1.x != 0 || p1.y != 0 || p1.z != 0 ) {
                mNormalList.push_back( glm::normalize( p1 ) );

            } else {
                mNormalList.push_back( p1 );
            }
        }
    }

    for( int y = 0; y < PLANESIZE - 1; y++ ) {
        for( int x = 0; x < PLANESIZE - 1; x++ ) {
            mIndexList.push_back( x + y*PLANESIZE );
            mIndexList.push_back( x + ( y+1 )*PLANESIZE );
            mIndexList.push_back( x+1 + y*PLANESIZE );
            mIndexList.push_back( x+1 + y*PLANESIZE );
            mIndexList.push_back( x + ( y+1 )*PLANESIZE );
            mIndexList.push_back( x+1 + ( y+1 )*PLANESIZE );
        }
    }

    MatrixControl.SetPosition( glm::vec3( 25, 100, 25 ) );
    mVertexBuffer.AddVectorData( mVertexList, sizeof( glm::vec3 ) );
    mVertexBuffer.SetAttributeIndex( mShader.GetAttribute( "Position" ) );
    mNormalBuffer.AddVectorData( mNormalList, sizeof( glm::vec3 ) );
    mNormalBuffer.SetAttributeIndex( mShader.GetAttribute( "Normal" ) );
    mIndexBuffer.AddVectorData( mIndexList, sizeof( unsigned int ) );
    mIndexBuffer.SetTarget( GL_ELEMENT_ARRAY_BUFFER );
    glm::mat4 Model = glm::translate( glm::vec3( -( PLANESIZE/2.0f ), 0, -( PLANESIZE/2.0f ) ) );
    mMVP = MatrixControl.PerspectiveView() * Model;
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
            Mouse::Set( Settings::Running.GetWidth()/2.0f, Settings::Running.GetHeight()/2.0f );
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

    glm::mat4 Model = glm::translate( glm::vec3( -50, 0, -50 ) );
    mMVP = MatrixControl.PerspectiveView() * Model;
}

void Program::Draw()
{
    glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    mShader.Bind();
    glUniformMatrix4fv( mShader.GetUniform( "MVP" ), 1, GL_FALSE, &mMVP[0][0] );
    mVertexBuffer.Bind( 3 );
    mNormalBuffer.Bind( 3 );
    mIndexBuffer.Bind();
    glDrawElements( GL_TRIANGLES, mIndexList.size(), GL_UNSIGNED_INT, ( void * )0 );
    mIndexBuffer.Unbind();
    mNormalBuffer.Unbind();
    mVertexBuffer.Unbind();
    Shader::Unbind();
    mDebugInfo.Draw();
}

const double Program::GetDelta()
{
    return mWindow->GetDelta();
}