#include "framework/Includes.hpp"

#include "Program.hpp"
#include "framework/Settings.hpp"
#include "framework/Utilities.hpp"
#include "framework/MatrixManager.hpp"

#include "framework/Input/Mouse.hpp"

#define PLANESIZE 50

Program::Program( Window *pWindow ) : mDebugInfo( pWindow )
{
    mWindow = pWindow;
    mShader.LoadShaderFiles( "./Resources/Terrain.vert" ,"./Resources/Terrain.frag" );
    mTerrainTexture.LoadFromFile( "./Resources/Textures.png" );
    int halfPlanet = PLANESIZE/2;

    for( int y = -halfPlanet; y < halfPlanet; y++ ) {
        for( int x = -halfPlanet; x < halfPlanet; x++ ) {
            float heightA = NoisePP.Generate( x, y ),
                  heightB = NoisePP.Generate( x + 1, y ),
                  heightC = NoisePP.Generate( x, y + 1 ),
                  heightD = NoisePP.Generate( x + 1, y + 1 );
            glm::vec3 p1( x, 0, y ),
                p2( x + 1, 0, y ),
                p3( x, 0, y + 1 ),
                p4( x + 1, 0, y + 1 );
            glm::vec2 tl( 0,0 ),
                tr( 1,0 ),
                bl( 0,1 ),
                br( 1,1 );
            mHeightList.push_back( heightA );
            mHeightList.push_back( heightB );
            mHeightList.push_back( heightC );
            mHeightList.push_back( heightD );
            mVertexList.push_back( p1 );
            mVertexList.push_back( p2 );
            mVertexList.push_back( p3 );
            mVertexList.push_back( p4 );
            mNormalList.push_back( tl );
            mNormalList.push_back( tr );
            mNormalList.push_back( bl );
            mNormalList.push_back( br );
            int size = mVertexList.size();
            mIndexList.push_back( size - 4 );
            mIndexList.push_back( size - 2 );
            mIndexList.push_back( size - 3 );
            mIndexList.push_back( size - 3 );
            mIndexList.push_back( size - 2 );
            mIndexList.push_back( size - 1 );
        }
    }

    MatrixControl.SetPosition( glm::vec3( 25, PLANESIZE, 25 ) );
    mVertexBuffer.AddVectorData( mVertexList, sizeof( glm::vec3 ) );
    mVertexBuffer.SetAttributeIndex( mShader.GetAttribute( "Position" ) );
    mHeightBuffer.AddVectorData( mHeightList, sizeof( float ) );
    mHeightBuffer.SetAttributeIndex( mShader.GetAttribute( "Height" ) );
    mNormalBuffer.AddVectorData( mNormalList, sizeof( glm::vec2 ) );
    mNormalBuffer.SetAttributeIndex( mShader.GetAttribute( "UV" ) );
    mIndexBuffer.AddVectorData( mIndexList, sizeof( unsigned int ) );
    mIndexBuffer.SetTarget( GL_ELEMENT_ARRAY_BUFFER );
    glm::mat4 Model = glm::mat4( 1.0f );
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
    mTerrainTexture.Bind();
    glUniform1i( mShader.GetUniform ( "TerrainTexture" ), 0 );
    mVertexBuffer.Bind( 3 );
    mNormalBuffer.Bind( 2 );
    mHeightBuffer.Bind( 1 );
    mIndexBuffer.Bind();
    glDrawElements( GL_TRIANGLES, mIndexList.size(), GL_UNSIGNED_INT, ( void * )0 );
    mIndexBuffer.Unbind();
    mHeightBuffer.Unbind();
    mNormalBuffer.Unbind();
    mVertexBuffer.Unbind();
    Texture::Unbind();
    Shader::Unbind();
    mDebugInfo.Draw();
}

const double Program::GetDelta()
{
    return mWindow->GetDelta();
}
