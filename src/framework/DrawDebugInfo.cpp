#include "DrawDebugInfo.hpp"

#include "Utilities.hpp"
#include "DebugOperators.hpp"
#include "ResourceManager.hpp"

DrawDebugInfo::DrawDebugInfo( Window *window )
{
    mWindow = window;
    mKBDivisor = 1/1024.0f;
    mDelta = ResourceManager::GetFont( "Default", "./Resources/fontBitmap.png" , "./Resources/bitmapMapping.txt" );
    mDelta->SetText( "" );
    mMemoryTotal = ResourceManager::GetFont( "Default", "./Resources/fontBitmap.png" , "./Resources/bitmapMapping.txt" );
    mMemoryTotal->SetText( "" );
    mMemoryNormal = ResourceManager::GetFont( "Default", "./Resources/fontBitmap.png" , "./Resources/bitmapMapping.txt" );
    mMemoryNormal->SetText( "" );
    mMemoryUnknown = ResourceManager::GetFont( "Default", "./Resources/fontBitmap.png" , "./Resources/bitmapMapping.txt" );
    mMemoryUnknown->SetText( "" );
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

    int startPos = 5;
    int displacement = 15;
    mDelta->SetPosition( glm::vec2( startPos, startPos ) );
    mDelta->SetText( "Frame time: " + Util::ToString( mWindow->GetDelta(), 3 ) );
    mDelta->Draw();
    mMemoryTotal->SetPosition( glm::vec2( startPos, startPos + displacement*1 ) );
    mMemoryTotal->SetText( "Total kb used: " + Util::ToString( MemoryUse::TotalBytesUsed * mKBDivisor, 2 ) );
    mMemoryTotal->Draw();
    mMemoryNormal->SetPosition( glm::vec2( startPos, startPos + displacement*2 ) );
    mMemoryNormal->SetText(  "Normal kb used: " + Util::ToString( MemoryUse::NormalBytesUsed * mKBDivisor, 2 ) );
    mMemoryNormal->Draw();
    mMemoryUnknown->SetPosition( glm::vec2( startPos, startPos + displacement*3 ) );
    mMemoryUnknown->SetText(  "Unknown kb used: " + Util::ToString( MemoryUse::UnknownBytesUsed * mKBDivisor, 2 ) );
    mMemoryUnknown->Draw();
}