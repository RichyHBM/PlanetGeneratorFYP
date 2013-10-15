#include "framework/Includes.hpp"

#include "Program.hpp"
#include "framework/Settings.hpp"
#include "framework/Utilities.hpp"


Program::Program( Window *pWindow )
{
    mWindow = pWindow;
    mBT.LoadFile( "./Resources/fontBitmap.png" , "./Resources/bitmapMapping.txt" );
    mBT.SetPosition( glm::vec2( 50, 50 ) );
    mBT.SetText( "Hello" );
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
    mBT.SetText( Util::ToString( mWindow->GetDelta() ) );
}

void Program::Draw()
{
    glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    mBT.Draw();
}

const double Program::GetDelta()
{
    return mWindow->GetDelta();
}