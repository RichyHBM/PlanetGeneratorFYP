#include "DrawDebugInfo.hpp"

#include "Utilities.hpp"
#include "DebugOperators.hpp"

DrawDebugInfo::DrawDebugInfo( Window *window )
{
    mWindow = window;
    int startPos = 5;
    int displacement = 15;
    mKBDivisor = 1/1024.0f;
    mDelta.LoadFile( "./Resources/fontBitmap.png" , "./Resources/bitmapMapping.txt" );
    mDelta.SetPosition( glm::vec2( startPos, startPos ) );
    mDelta.SetText( "" );
    mMemoryTotal.LoadFile( "./Resources/fontBitmap.png" , "./Resources/bitmapMapping.txt" );
    mMemoryTotal.SetPosition( glm::vec2( startPos, startPos + displacement*1 ) );
    mMemoryTotal.SetText( "" );
    mMemoryNormal.LoadFile( "./Resources/fontBitmap.png" , "./Resources/bitmapMapping.txt" );
    mMemoryNormal.SetPosition( glm::vec2( startPos, startPos + displacement*2 ) );
    mMemoryNormal.SetText( "" );
    mMemoryUnknown.LoadFile( "./Resources/fontBitmap.png" , "./Resources/bitmapMapping.txt" );
    mMemoryUnknown.SetPosition( glm::vec2( startPos, startPos + displacement*3 ) );
    mMemoryUnknown.SetText( "" );
    mDraw = true;
}

DrawDebugInfo::~DrawDebugInfo()
{
}

void DrawDebugInfo::SetDraw( bool draw )
{
    mDraw = draw;
}

void DrawDebugInfo::ToggleDraw()
{
	mDraw = !mDraw;
}

void DrawDebugInfo::Draw()
{
    if( !mDraw ) {
        return;
    }

    mDelta.SetText( "Frame time: " + Util::ToString( mWindow->GetDelta(), 3 ) );
    mMemoryTotal.SetText( "Total kb used: " + Util::ToString( MemoryUse::TotalBytesUsed * mKBDivisor, 2 ) );
    mMemoryNormal.SetText(  "Normal kb used: " + Util::ToString( MemoryUse::NormalBytesUsed * mKBDivisor, 2 ) );
    mMemoryUnknown.SetText(  "Unknown kb used: " + Util::ToString( MemoryUse::UnknownBytesUsed * mKBDivisor, 2 ) );
    mDelta.Draw();
    mMemoryTotal.Draw();
    mMemoryNormal.Draw();
    mMemoryUnknown.Draw();
}