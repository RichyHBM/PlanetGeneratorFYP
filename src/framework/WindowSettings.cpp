#include "WindowSettings.hpp"
#include "Utilities.hpp"

WindowSettings WindowSettings::Initial;
WindowSettings WindowSettings::Running;

void WindowSettings::ParseArguments( const std::string &arg, const std::string &arg2 )
{
    if( arg == "-depth" ) {
        Initial.mDepthBits = Util::StrTo<short>( arg2 );

    } else if( arg == "-stencil" ) {
        Initial.mStencilBits = Util::StrTo<short>( arg2 );

    } else if( arg == "-antialiasing" ) {
        Initial.mAntiAliasing = Util::StrTo<short>( arg2 );

    } else if( arg == "-width" ) {
        Initial.mWidth = Util::StrTo<short>( arg2 );
        Initial.mAspectRatio = Initial.mWidth/( float )Initial.mHeight;

    } else if( arg == "-height" ) {
        Initial.mHeight = Util::StrTo<short>( arg2 );
        Initial.mAspectRatio = Initial.mWidth/( float )Initial.mHeight;

    } else if( arg == "-vsynk" ) {
        if( Util::StrTo<short>( arg2 ) == 1 ) {
            Initial.mVSynk = true;

        } else {
            Initial.mVSynk = false;
        }

    } else if( arg == "-fullsceen" ) {
        if( Util::StrTo<short>( arg2 ) == 1 ) {
            Initial.mFullScreen = true;

        } else {
            Initial.mFullScreen = false;
        }

    } else if( arg == "-fps" ) {
        Initial.mFPS = Util::StrTo<short>( arg2 );
    }
}

WindowSettings::WindowSettings()
{
}

WindowSettings::~WindowSettings()
{
}

void WindowSettings::SetSettings(
    unsigned short pDepthBits,
    unsigned short pStencilBits,
    unsigned short pAntiAliasing,
    unsigned short pMajorOGL,
    unsigned short pMinorOGL,
    unsigned short pWidth,
    unsigned short pHeight,
    unsigned short pFPS,
    bool pVSynk,
    bool pFullScreen )
{
    mDepthBits = pDepthBits;
    mStencilBits = pStencilBits;
    mAntiAliasing = pAntiAliasing;
    mMajorOGL = pMajorOGL;
    mMinorOGL = pMinorOGL;
    mWidth = pWidth;
    mHeight = pHeight;
    mFPS = pFPS;
    mVSynk = pVSynk;
    mFullScreen = pFullScreen;
    mAspectRatio = pWidth/( float )pHeight;
}

void WindowSettings::SetResolution(
    unsigned short pWidth,
    unsigned short pHeight )
{
    mWidth = pWidth;
    mHeight = pHeight;
    //Recompute aspect ratio
    mAspectRatio = pWidth/( float )pHeight;
}

unsigned short WindowSettings::GetDepthBits()
{
    return mDepthBits;
}

unsigned short WindowSettings::GetStencilBits()
{
    return mStencilBits;
}

unsigned short WindowSettings::GetAntiAliasing()
{
    return mAntiAliasing;
}

unsigned short WindowSettings::GetMajorOGL()
{
    return mMajorOGL;
}

unsigned short WindowSettings::GetMinorOGL()
{
    return mMinorOGL;
}

unsigned short WindowSettings::GetWidth()
{
    return mWidth;
}

unsigned short WindowSettings::GetHeight()
{
    return mHeight;
}

float WindowSettings::GetAspectRatio()
{
    return mAspectRatio;
}

unsigned short WindowSettings::GetFPS()
{
    return mFPS;
}

bool WindowSettings::GetVSynk()
{
    return mVSynk;
}

bool WindowSettings::GetFullScreen()
{
    return mFullScreen;
}
