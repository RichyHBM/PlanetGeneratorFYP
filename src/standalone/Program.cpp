#include "framework/Includes.hpp"

#include "Program.hpp"
#include "framework/Settings.hpp"
#include "framework/Utilities.hpp"
#include "framework/MatrixManager.hpp"

Program::Program( Window *pWindow ) : mDebugInfo( pWindow )
{
    mWindow = pWindow;
    std::string vertexShader = GLSL(
                                   uniform mat4 MVP;
                                   attribute vec4 Position;
								   attribute vec3 Normal;
								   varying vec3 normal;
									void main() {
										normal = Normal;
										gl_Position =  MVP * Position;
									} 
	);

    std::string fragmentShader = GLSL(
								varying vec3 normal;
								void main() {
									gl_FragColor = vec4( normal.xyz, 1.0 );
								} 
	);

    mShader.LoadShaderCode( vertexShader ,fragmentShader );

    for(int y = 0; y < 100; y++)
	{
		for(int x = 0; x < 100; x++)
		{
			glm::vec3 p1( x, NoisePP.Generate(x, y) * 50, y );
			mVertexList.push_back(p1);
		}
	}

	for(int y = 0; y < 99; y++)
	{
		for(int x = 0; x < 99; x++)
		{
			mIndexList.push_back(x + y*100);
			mIndexList.push_back(x + (y+1)*100 );
			mIndexList.push_back(x+1 + y*100);

			mIndexList.push_back(x+1 + y*100);
			mIndexList.push_back(x + (y+1)*100);
			mIndexList.push_back(x+1 + (y+1)*100);
		}
	}

	MatrixControl.SetPosition(glm::vec3(25, 100, 25));
    mVertexBuffer.AddVectorData( mVertexList, sizeof( glm::vec3 ) );
    mVertexBuffer.SetAttributeIndex( mShader.GetAttribute( "Position" ) );
    
//	mNormalBuffer.AddVectorData( mNormalList, sizeof( glm::vec3 ) );
//    mNormalBuffer.SetAttributeIndex( mShader.GetAttribute( "Normal" ) );

	mIndexBuffer.AddVectorData( mIndexList, sizeof( unsigned int ) );
	mIndexBuffer.SetTarget(GL_ELEMENT_ARRAY_BUFFER);

	glm::mat4 Model = glm::translate(glm::vec3(-50, 0, -50));
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
    if( sf::Keyboard::isKeyPressed( sf::Keyboard::F10 ) ) {
        mDebugInfo.SetDraw( true );
    }

    if( sf::Keyboard::isKeyPressed( sf::Keyboard::F11 ) ) {
        mDebugInfo.SetDraw( false );
    }
}

void Program::Draw()
{
    glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    mShader.Bind();
    glUniformMatrix4fv( mShader.GetUniform( "MVP" ), 1, GL_FALSE, &mMVP[0][0] );
    mVertexBuffer.Bind( 3 );
//	mNormalBuffer.Bind( 3 );
	mIndexBuffer.Bind();
    glDrawElements( GL_TRIANGLES, mIndexList.size(), GL_UNSIGNED_INT, (void*)0 );
	mIndexBuffer.Unbind();
//	mNormalBuffer.Unbind();
    mVertexBuffer.Unbind();
    Shader::Unbind();
    mDebugInfo.Draw();
}

const double Program::GetDelta()
{
    return mWindow->GetDelta();
}