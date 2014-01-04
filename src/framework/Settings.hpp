#ifndef SETTINGS_HPP
#define SETTINGS_HPP

#include <string>

class Settings
{
public:
    //Startup settings
    static Settings Initial;
    //Real run time settings
    static Settings Running;

    static void ParseArguments( const std::string &arg, const std::string &arg2 );

    Settings();
    ~Settings();
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
        bool pFullScreen );

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
};

#endif // SETTINGS_HPP
