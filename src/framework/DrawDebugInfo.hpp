#ifndef DRAWDEBUGINFO_HPP
#define DRAWDEBUGINFO_HPP

#include "Includes.hpp"
#include "GLHelp/BitmapText.hpp"
#include "Window.hpp"

class DrawDebugInfo
{
public:
    DrawDebugInfo( Window *window );
    ~DrawDebugInfo();
    void SetDraw( bool draw );
    void Draw();
    void ToggleDraw();
    void SetVertices(int v);

protected:
    float mKBDivisor;
    bool mDraw;
    Window *mWindow;
    BitmapText *mDelta;
    BitmapText *mMemoryTotal;
    BitmapText *mTotalVertices;
    int mVertices;
};

#endif