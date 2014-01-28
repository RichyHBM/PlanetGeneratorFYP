#ifndef DRAWDEBUGINFO_HPP
#define DRAWDEBUGINFO_HPP

#include "../Includes.hpp"
#include "../GLHelp/BitmapText.hpp"
#include "../Window/Window.hpp"

class DrawDebugInfo
{
public:
    DrawDebugInfo( Window *window );
    ~DrawDebugInfo();
    void SetDraw( bool draw );
    void Draw();
    void ToggleDraw();
    void SetVertices( int v );
    void SetDrawRebuild();
protected:
    float mKBDivisor;
    bool mDraw;
    bool mRebuilding;
    Window *mWindow;
    BitmapText *mDelta;
    BitmapText *mMemoryTotal;
    BitmapText *mTotalVertices;
    BitmapText *mRebuildingText;
    int mVertices;
};

#endif