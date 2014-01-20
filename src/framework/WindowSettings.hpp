#ifndef WINDOWSETTINGS_HPP
#define WINDOWSETTINGS_HPP

#include <string>

class WindowSettings
{
public:
    //Startup settings
    static WindowSettings Initial;
    //Real run time settings
    static WindowSettings Running;

    static void ParseArguments( const std::string &arg, const std::string &arg2 );

    WindowSettings();
    ~WindowSettings();
    unsigned short GetDepthBits();
    unsigned short GetStencilBits();
    unsigned short GetAntiAliasing();
    unsigned short GetMajorOGL();
    unsigned short GetMinorOGL();
    unsigned short GetWidth();
    unsigned short GetHeight();
    float GetAspectRatio();
    unsigned short GetFPS();
    bool GetVSynk();
    bool GetFullScreen();
    bool UseTweakBar();
    
    ///
    ///Set all parameters of the settings instance
    ///
    void SetSettings(
        unsigned short pDepthBits,
        unsigned short pStencilBits,
        unsigned short pAntiAliasing,
        unsigned short pMajorOGL,
        unsigned short pMinorOGL,
        unsigned short pWidth,
        unsigned short pHeight,
        unsigned short pFPS,
        bool pVSynk,
        bool pFullScreen,
        bool pUseTweakBar );

    ///
    ///Setter for the width and height
    ///
    void SetResolution(
        unsigned short pWidth,
        unsigned short pHeight );

protected:
private:
    unsigned short mDepthBits;
    unsigned short mStencilBits;
    unsigned short mAntiAliasing;
    unsigned short mMajorOGL;
    unsigned short mMinorOGL;
    unsigned short mWidth;
    unsigned short mHeight;
    unsigned short mFPS;
    float mAspectRatio;
    bool mVSynk;
    bool mFullScreen;
    bool mUseTweakBar;
};

#endif // WINDOWSETTINGS_HPP
