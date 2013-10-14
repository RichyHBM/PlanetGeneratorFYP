#ifndef WINDOWGLFW_HPP
#define WINDOWGLFW_HPP

#ifdef GLFW

#include "Includes.hpp"
#include "Window.hpp"

class WindowGLFW : public Window
{
public:
    WindowGLFW();
    virtual ~WindowGLFW();

    bool IsFocused();
    bool IsOpen();
	//Returns the GLFW window pointer
    GLFWwindow *GetGLFWWindow();
    void SetCursor( CursorState pState );
    void DoEvents();
    void Display();
    bool IsWindowCreated();
    void MakeContextCurrent();
    void ResetDelta();
    void Close();
private:
    GLFWwindow *mWindow;
    static bool mGLFWInitialised;
    static int mWindowCount;
};

#endif //GLFW

#endif // WINDOWGLFW_HPP
