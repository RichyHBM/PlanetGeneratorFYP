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
    Window() {}
    virtual ~Window() {}

    virtual bool IsFocused() = 0;
    virtual bool IsOpen() =0;
    virtual void SetCursor( CursorState pState ) =0;
    double GetDelta() {
        return mDelta;
    }
    virtual void DoEvents()=0;
    virtual void Display() =0;
    virtual bool IsWindowCreated()=0;
    virtual void MakeContextCurrent()=0;
    virtual void ResetDelta()=0;
    virtual void Close()=0;
protected:
    double mDelta;
};
#endif // WINDOW_HPP