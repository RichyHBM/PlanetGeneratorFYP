#include "Settings.hpp"
#include "Utilities.hpp"

Settings Settings::Initial;
Settings Settings::Running;

void Settings::ParseArguments( int argc, const char *argv[] )
{
    for( int i = 1; i < argc; i++ ) {
        if( argv[i] == "-depth" && argc > i+1 ) {
            Initial.mDepthBits = Util::StrTo<short>( argv[i+1] );

        } else if( argv[i] == "-stencil" && argc > i+1 ) {
            Initial.mStencilBits = Util::StrTo<short>( argv[i+1] );

        } else if( argv[i] == "-antialiasing" && argc > i+1 ) {
            Initial.mAntiAliasing = Util::StrTo<short>( argv[i+1] );

        } else if( argv[i] == "-width" && argc > i+1 ) {
            Initial.mWidth = Util::StrTo<short>( argv[i+1] );
            Initial.mAspectRatio = Initial.mWidth/( float )Initial.mHeight;

        } else if( argv[i] == "-height" && argc > i+1 ) {
            Initial.mHeight = Util::StrTo<short>( argv[i+1] );
            Initial.mAspectRatio = Initial.mWidth/( float )Initial.mHeight;

        } else if( argv[i] == "-vsynk" && argc > i+1 ) {
            if( Util::StrTo<short>( argv[i+1] ) == 1 ) {
                Initial.mVSynk = true;

            } else {
                Initial.mVSynk = false;
            }

        } else if( argv[i] == "-fullsceen" && argc > i+1 ) {
            if( Util::StrTo<short>( argv[i+1] ) == 1 ) {
                Initial.mFullScreen = true;

            } else {
                Initial.mFullScreen = false;
            }

        } else if( argv[i] == "-fps" && argc > i+1 ) {
            Initial.mFPS = Util::StrTo<short>( argv[i+1] );
        }
    }
}

Settings::Settings()
{
}

Settings::~Settings()
{
}

void Settings::SetSettings(
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

void Settings::SetResolution(
    unsigned short pWidth,
    unsigned short pHeight )
{
    mWidth = pWidth;
    mHeight = pHeight;
    //Recompute aspect ratio
    mAspectRatio = pWidth/( float )pHeight;
}

unsigned short Settings::GetDepthBits()
{
    return mDepthBits;
}

unsigned short Settings::GetStencilBits()
{
    return mStencilBits;
}

unsigned short Settings::GetAntiAliasing()
{
    return mAntiAliasing;
}

unsigned short Settings::GetMajorOGL()
{
    return mMajorOGL;
}

unsigned short Settings::GetMinorOGL()
{
    return mMinorOGL;
}

unsigned short Settings::GetWidth()
{
    return mWidth;
}

unsigned short Settings::GetHeight()
{
    return mHeight;
}

float Settings::GetAspectRatio()
{
    return mAspectRatio;
}

unsigned short Settings::GetFPS()
{
    return mFPS;
}

bool Settings::GetVSynk()
{
    return mVSynk;
}

bool Settings::GetFullScreen()
{
    return mFullScreen;
}
