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
    //Change whether to draw this information or not
    void SetDraw( bool draw );
    void ToggleDraw();

    void Draw();
    //Set the vertice count
    void SetVertices( int v );
    //Draw the "rebuilding" text
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