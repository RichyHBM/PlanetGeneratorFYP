#ifndef WINDOW_HPP
#define WINDOW_HPP

#include "../Includes.hpp"

// Window interface, any windowing library wrapper must implement these methods.

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
    bool NeedsToClose() {
        return mNeedsClose;
    }
    //Processes the events queue
    virtual void DoEvents()=0;
    virtual void Display() =0;
    virtual bool IsWindowCreated()=0;
    //Sets this window to be the current OpenGL context
    virtual void MakeContextCurrent()=0;
    virtual void ResetDelta()=0;
    virtual void Close()=0;

    void SaveGLStates() {
        glPushClientAttrib( GL_CLIENT_ALL_ATTRIB_BITS );
        Util::PrintGLErrors();
        glPushAttrib( GL_ALL_ATTRIB_BITS );
        Util::PrintGLErrors();
        glMatrixMode( GL_MODELVIEW );
        Util::PrintGLErrors();
        glPushMatrix();
        Util::PrintGLErrors();
        glMatrixMode( GL_PROJECTION );
        Util::PrintGLErrors();
        glPushMatrix();
        Util::PrintGLErrors();
        glMatrixMode( GL_TEXTURE );
        Util::PrintGLErrors();
        glPushMatrix();
        Util::PrintGLErrors();
    }

    void RestoreGLStates() {
        glMatrixMode( GL_PROJECTION );
        Util::PrintGLErrors();
        glPopMatrix();
        Util::PrintGLErrors();
        glMatrixMode( GL_MODELVIEW );
        Util::PrintGLErrors();
        glPopMatrix();
        Util::PrintGLErrors();
        glMatrixMode( GL_TEXTURE );
        Util::PrintGLErrors();
        glPopMatrix();
        Util::PrintGLErrors();
        glPopClientAttrib();
        Util::PrintGLErrors();
        glPopAttrib();
        Util::PrintGLErrors();
    }
protected:
    double mDelta;
    bool mNeedsClose;
};
#endif // WINDOW_HPP