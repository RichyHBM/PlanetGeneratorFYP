#include "DrawDebugInfo.hpp"

#include "Utilities.hpp"
#include "DebugOperators.hpp"

DrawDebugInfo::DrawDebugInfo( Window *window )
{
    mWindow = window;
    int startPos = 5;
    int displacement = 15;
    mDelta.LoadFile( "./Resources/fontBitmap.png" , "./Resources/bitmapMapping.txt" );
    mDelta.SetPosition( glm::vec2( startPos, startPos ) );
    mDelta.SetText( "" );
    mMemoryTotal.LoadFile( "./Resources/fontBitmap.png" , "./Resources/bitmapMapping.txt" );
    mMemoryTotal.SetPosition( glm::vec2( startPos, startPos + displacement ) );
    mMemoryTotal.SetText( "" );
    mMemoryAssets.LoadFile( "./Resources/fontBitmap.png" , "./Resources/bitmapMapping.txt" );
    mMemoryAssets.SetPosition( glm::vec2( startPos, startPos + displacement*2 ) );
    mMemoryAssets.SetText( "" );
    mMemoryGraphics.LoadFile( "./Resources/fontBitmap.png" , "./Resources/bitmapMapping.txt" );
    mMemoryGraphics.SetPosition( glm::vec2( startPos, startPos + displacement*3 ) );
    mMemoryGraphics.SetText( "" );
    mMemoryNormal.LoadFile( "./Resources/fontBitmap.png" , "./Resources/bitmapMapping.txt" );
    mMemoryNormal.SetPosition( glm::vec2( startPos, startPos + displacement*4 ) );
    mMemoryNormal.SetText( "" );
    mMemoryUnknown.LoadFile( "./Resources/fontBitmap.png" , "./Resources/bitmapMapping.txt" );
    mMemoryUnknown.SetPosition( glm::vec2( startPos, startPos + displacement*5 ) );
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

void DrawDebugInfo::Draw()
{
    if( !mDraw ) {
        return;
    }

    mDelta.SetText( "Frame time: " + Util::ToString( mWindow->GetDelta() ) );
    mMemoryTotal.SetText( "Total bytes used: " + Util::ToString( MemoryUse::TotalBytesUsed	 ) );
    mMemoryAssets.SetText(  "Asset bytes used: " + Util::ToString( MemoryUse::AssetsBytesUsed	) );
    mMemoryGraphics.SetText(  "Graphics bytes used: " + Util::ToString( MemoryUse::GraphicsBytesUsed	) );
    mMemoryNormal.SetText(  "Normal bytes used: " + Util::ToString( MemoryUse::NormalBytesUsed	) );
    mMemoryUnknown.SetText(  "Unknown bytes used: " + Util::ToString( MemoryUse::UnknownBytesUsed	) );
    mDelta.Draw();
    mMemoryTotal.Draw();
    mMemoryAssets.Draw();
    mMemoryGraphics.Draw();
    mMemoryNormal.Draw();
    mMemoryUnknown.Draw();
}