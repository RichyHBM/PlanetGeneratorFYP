#include "Includes.hpp"

#include "Program.hpp"
#include "./Settings.hpp"
#include "./Utilities.hpp"


Program::Program( Window *pWindow )
{
	mWindow = pWindow;
}

Program::~Program()
{
	mWindow = NULL;
    //dtor
}

void Program::Run()
{
    while( mWindow->IsOpen() ) {

		mWindow->DoEvents();

        if( mWindow->IsFocused() ) {
            mWindow->MakeContextCurrent();
            mWindow->SetCursor( CursorState::Hidden );
        }

        if( !mWindow->IsFocused() ) {
            mWindow->SetCursor( CursorState::Shown );
        }

        if( mWindow->IsFocused() ) {
            if( !mWindow->IsOpen() ) {
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
}

void Program::Draw()
{
    glClearColor( 1.0f, 0.0f, 0.0f, 1.0f );
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
}

const double Program::GetDelta()
{
	return mWindow->GetDelta();
}