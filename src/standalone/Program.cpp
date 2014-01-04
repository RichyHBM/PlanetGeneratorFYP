#include "framework/Includes.hpp"

#include "Program.hpp"
#include "framework/Settings.hpp"
#include "framework/Utilities.hpp"
#include "framework/MatrixManager.hpp"

#include "framework/Input/Mouse.hpp"

#define PLANESIZE 200
#define HEIGHTAMOUNT 50

Program::Program( Window *pWindow ) : mDebugInfo( pWindow )
{
	mWindow = pWindow;

	mShader.LoadShaderFiles( "./Resources/Terrain.vert" ,"./Resources/Terrain.frag" );

	int halfPlanet = PLANESIZE/2;
	for( int y = -halfPlanet; y < halfPlanet; y++ ) {
		for( int x = -halfPlanet; x < halfPlanet; x++ ) {
			glm::vec3 p1( x, halfPlanet , y );
			mVertexList.push_back( p1 );

			glm::vec4 noiseVec( 0.0, 0.0, 0.0, NoisePP.Generate( x*0.3, y*0.3 ));
			mHeightList.push_back( noiseVec );
			
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
	mHeightBuffer.AddVectorData( mHeightList, sizeof( glm::vec4 ) );
	mHeightBuffer.SetAttributeIndex( mShader.GetAttribute( "Height" ) );
	mIndexBuffer.AddVectorData( mIndexList, sizeof( unsigned int ) );
	mIndexBuffer.SetTarget( GL_ELEMENT_ARRAY_BUFFER );

	glm::mat4 Model = glm::mat4(1.0f);

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
	glUniform1f( mShader.GetUniform( "Radius" ), PLANESIZE/2.0 );
	glUniform1f( mShader.GetUniform( "HeightTimes" ), HEIGHTAMOUNT);
	mVertexBuffer.Bind( 3 );
	mNormalBuffer.Bind( 3 );
	mHeightBuffer.Bind( 4 );
	mIndexBuffer.Bind();
	glDrawElements( GL_TRIANGLES, mIndexList.size(), GL_UNSIGNED_INT, ( void * )0 );
	mIndexBuffer.Unbind();
	mHeightBuffer.Unbind();
	mNormalBuffer.Unbind();
	mVertexBuffer.Unbind();
	Shader::Unbind();
	mDebugInfo.Draw();
}

const double Program::GetDelta()
{
	return mWindow->GetDelta();
}
