#include "framework/Includes.hpp"

#include "Program.hpp"
#include "framework/Settings.hpp"
#include "framework/Utilities.hpp"


Program::Program( Window *pWindow ) : mDebugInfo( pWindow )
{
    mWindow = pWindow;
    std::string vertexShader = GLSL(
                                   uniform mat4 MVP;
                                   attribute vec4 Position;
    void main() {
        gl_Position =  MVP * Position;
    } );
    std::string fragmentShader = GLSL(
    void main() {
        gl_FragColor = vec4( 1.0, 0.0, 0.0, 1.0 );
    } );
    mShader.LoadShaderCode( vertexShader ,fragmentShader );
    mVertexList.push_back( glm::vec3( 0.0f, 0.5f, 0.0f ) );
    mVertexList.push_back( glm::vec3( 0.5f, -0.5f, 0.0f ) );
    mVertexList.push_back( glm::vec3( -0.5f, -0.5f, 0.0f ) );
    mVertexBuffer.AddVectorData( mVertexList, sizeof( glm::vec3 ) );
    mVertexBuffer.SetAttributeIndex( mShader.GetAttribute( "Position" ) );
    glm::mat4 Projection = glm::perspective( 75.0f, Settings::Running.GetAspectRatio(), 0.1f, 100.0f );
    glm::mat4 View       = glm::lookAt(
                               glm::vec3( 0,0,-2 ),
                               glm::vec3( 0,0,0 ),
                               glm::vec3( 0,1,0 )
                           );
    glm::mat4 Model      = glm::mat4( 1.0f );
    mMVP        = Projection * View * Model;
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
    glDrawArrays( GL_TRIANGLES, 0, mVertexList.size() );
    mVertexBuffer.Unbind();
    Shader::Unbind();
    mDebugInfo.Draw();
}

const double Program::GetDelta()
{
    return mWindow->GetDelta();
}