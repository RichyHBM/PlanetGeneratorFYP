#include "Includes.hpp"

#include "Program.hpp"

#include "./Keyboard.hpp"
#include "./Settings.hpp"
#include "./Utilities.hpp"

#include <GLFW/glfw3.h>

Program::Program(GLFWwindow* window)
{
    mWindow = window;
	mBT.LoadFile("./Resources/cBitmap.png", "./Resources/cInfo.h.txt");
    mBT.SetPosition(glm::vec2(10,5));
    mBT.SetColor(1.0f , 1.0f, 1.0f , 1.0f);
	mBT.SetText("Hello");
}

Program::~Program()
{
    //dtor
}

void Program::Run()
{
    bool focused = true;

    double upTime = 1.0 / Settings::Running.GetFPS();
	

    while(!glfwWindowShouldClose( mWindow ))
    {
        KeyBoard::keyboard.Update(mWindow);

        if(KeyBoard::keyboard.HasKeyBeenPressed(GLFW_KEY_ESCAPE) )
		{
            Close();
		}
		

        if(glfwGetWindowAttrib( mWindow, GLFW_FOCUSED) == GL_TRUE)
        {
            focused = true;
			glfwMakeContextCurrent(mWindow);
            glfwSetInputMode( mWindow, GLFW_CURSOR, GLFW_CURSOR_HIDDEN  );
        }

        if(glfwGetWindowAttrib( mWindow, GLFW_FOCUSED) == GL_FALSE)
        {
            focused = false;
            glfwSetInputMode( mWindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL  );
        }

        if(focused)
		{
            HandleEvents();
		}
		
        if(focused)
        {

            if(glfwWindowShouldClose( mWindow )){
				break;
			}

            Update();

            double delta = glfwGetTime();
            if(delta < 0.0) delta = 0.0;
            //glfwSleep(upTime - delta);
            mDelta = glfwGetTime();
            glfwSetTime( 0.0 );

            Draw();

            glfwSwapBuffers(mWindow);
			glfwPollEvents();

            Util::PrintGLErrors();
        }
        else
        {
            glfwSwapBuffers(mWindow);
			glfwPollEvents();
        }
    }

	glfwDestroyWindow(mWindow);

}

void Program::HandleEvents()
{
    

}

void Program::Update()
{

}

void Program::Draw()
{
    glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
	mBT.Draw();
}

const double Program::GetDelta()
{
    return mDelta;
}

void Program::Close()
{
    glfwSetWindowShouldClose(mWindow, GL_TRUE);
}