#include "DrawDebugInfo.hpp"

#include "../Utilities.hpp"
#include "DebugOperators.hpp"
#include "../Managers/ResourceManager.hpp"
#include "../Window/WindowSettings.hpp"

DrawDebugInfo::DrawDebugInfo( Window *window )
{
    mWindow = window;
    mKBDivisor = 1/1024.0f;
    mDelta = ResourceManager::GetFont( "Default", "./Resources/fontBitmap.png" , "./Resources/bitmapMapping.txt" );
    mDelta->SetText( "" );
    mMemoryTotal = ResourceManager::GetFont( "Default", "./Resources/fontBitmap.png" , "./Resources/bitmapMapping.txt" );
    mMemoryTotal->SetText( "" );
    mTotalVertices = ResourceManager::GetFont( "Default", "./Resources/fontBitmap.png" , "./Resources/bitmapMapping.txt" );
    mTotalVertices->SetText( "" );
    mRebuildingText = ResourceManager::GetFont( "Default", "./Resources/fontBitmap.png" , "./Resources/bitmapMapping.txt" );
    mRebuildingText->SetText( "Rebuilding!" );
    mDraw = true;
    mVertices =0;
    mRebuilding = false;
}

DrawDebugInfo::~DrawDebugInfo()
{
}

void DrawDebugInfo::SetDrawRebuild()
{
    mRebuilding = true;
}

void DrawDebugInfo::SetDraw( bool draw )
{
    mDraw = draw;
}

void DrawDebugInfo::ToggleDraw()
{
    mDraw = !mDraw;
}

void DrawDebugInfo::SetVertices( int v )
{
    mVertices = v;
}

void DrawDebugInfo::Draw()
{
    if( !mDraw ) {
        return;
    }

    int startPos = 5;
    int displacement = 15;
    mDelta->SetPosition( glm::vec2( startPos, startPos ) );
    mDelta->SetText( "Frame time: " + Util::ToString( mWindow->GetDelta(), 3 ) );
    mDelta->Draw();
    mMemoryTotal->SetPosition( glm::vec2( startPos, startPos + displacement*1 ) );
    mMemoryTotal->SetText( "Total kb used: " + Util::ToString( MemoryUse::TotalBytesUsed * mKBDivisor, 2 ) );
    mMemoryTotal->Draw();
    mTotalVertices->SetPosition( glm::vec2( startPos, startPos + displacement*2 ) );
    mTotalVertices->SetText(  "Total Vertices: " + Util::ToString( mVertices ) );
    mTotalVertices->Draw();

    if( mRebuilding ) {
        mRebuildingText->SetPosition( glm::vec2( WindowSettings::Running.GetWidth()/2, WindowSettings::Running.GetHeight()/2 ) );
        mRebuildingText->SetText( "Rebuilding!" );
        mRebuildingText->Draw();
        mRebuilding = false;
    }
}