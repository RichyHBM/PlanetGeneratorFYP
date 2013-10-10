#include "Settings.hpp"

Settings Settings::Initial;
Settings Settings::Running;

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
