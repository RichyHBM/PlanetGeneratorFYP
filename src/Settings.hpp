#ifndef SETTINGS_HPP
#define SETTINGS_HPP


class Settings
{
public:
    ///
    ///Initial settings
    ///
    static Settings Initial;
    ///
    ///Running settings
    ///
    static Settings Running;
    ///
    ///Default constructor
    ///
    Settings();
    ///
    ///Default destructor
    ///
    ~Settings();
    ///
    ///Getter for the depth bits
    ///
    unsigned short GetDepthBits();
    ///
    ///Getter for the stencil bits
    ///
    unsigned short GetStencilBits();
    ///
    ///Getter for the antialiasing level
    ///
    unsigned short GetAntiAliasing();
    ///
    ///Getter for the openGL major version
    ///
    unsigned short GetMajorOGL();
    ///
    ///Getter for the openGL minor version
    ///
    unsigned short GetMinorOGL();
    ///
    ///Getter for the window width
    ///
    unsigned short GetWidth();
    ///
    ///Getter for the window height
    ///
    unsigned short GetHeight();
    ///
    ///Getter for the target fps
    ///
    unsigned short GetFPS();
    ///
    ///Getter for the vsynk boolean
    ///
    bool GetVSynk();
    ///
    ///Getter for the fullscreen boolean
    ///
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
        bool pFullScreen);

    ///
    ///Seeter for the qidth and height
    ///
    void SetResolution(
        unsigned short pWidth,
        unsigned short pHeight);

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
