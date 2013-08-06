#ifndef WINDOW_HPP
#define WINDOW_HPP

#include "Includes.hpp"

enum CursorState {
    Hidden,
    Shown,
    Locked
};

class Window
{
public:
    Window();
    ~Window();

    bool IsFocused();
    bool IsOpen();
    GLFWwindow *GetGLFWWindow();
    void SetCursor( CursorState pState );
    double GetDelta();
    void SwapBuffersAndPollEvents();
    bool IsWindowCreated();
    void MakeContextCurrent();
    void ResetDelta();
    void Close();
private:
    GLFWwindow *mWindow;
    static bool mGLFWInitialised;
    static int mWindowCount;
    double mDelta;
};

#endif // WINDOW_HPP
