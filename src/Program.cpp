#include "Program.hpp"

#include "./Keyboard.hpp"

#include <GL/glfw.h>

Program::Program()
{
    
}

Program::~Program()
{
    //dtor
}

void Program::Run()
{
    bool focused = true;
    mRunning = true;

    double upTime = 1.0 / Settings::Running.GetFPS();

    while(mRunning)
    {
        KeyBoard::keyboard.Update();

        if(KeyBoard::keyboard.HasKeyBeenPressed(GLFW_KEY_ESC) )
		{
            Close();
		}
		
        if(glfwGetWindowParam(GLFW_OPENED) == GL_FALSE)
		{
			Close();
		}

        if(glfwGetWindowParam(GLFW_ACTIVE) == GL_TRUE)
        {
            focused = true;
            glfwDisable( GLFW_MOUSE_CURSOR );
        }

        if(glfwGetWindowParam(GLFW_ACTIVE) == GL_FALSE)
        {
            focused = false;
            glfwEnable( GLFW_MOUSE_CURSOR );
        }

        if(focused)
		{
            HandleEvents();
		}
		
        if(focused)
        {

            if(!mRunning){
				break;
			}

            Update();

            double delta = glfwGetTime();
            if(delta < 0.0) delta = 0.0;
            glfwSleep(upTime - delta);
            mDelta = glfwGetTime();
            glfwSetTime( 0.0 );

            Draw();

            glfwSwapBuffers();

            PrintGLErrors();
        }
        else
        {
            glfwSwapBuffers();
        }
    }

}

void Program::HandleEvents()
{
    

}

void Program::Update()
{
    
}

void Program::Draw()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
	
}

const double Program::GetDelta()
{
    return mDelta;
}

void Program::Close()
{
    mRunning = false;
}