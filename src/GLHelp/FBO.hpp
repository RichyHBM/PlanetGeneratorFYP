#ifndef FBO_HPP
#define FBO_HPP

#include "../Includes.hpp"

class FBO
{
public:
    ///
    ///Default constructor
    ///
    FBO();
    ///
    ///Default destructor
    ///
    ~FBO();
    ///
    ///Get the FBO ID
    ///
    GLuint GetFBO();
    ///
    ///Get the depth buffers ID
    ///
    GLuint GetDepthBuffer();
    ///
    ///Get the textures ID
    ///
    GLuint GetTexture();
    ///
    ///Create an FBO of the given size
    ///
    bool Create(int pWidth, int pHeight);
    ///
    ///Bind the FBO
    ///
    void Bind();
    ///
    ///Unbind all FBO's
    ///
    static void Unbind();
    ///
    ///Clear the FBO
    ///
    void Clear(float pRed = 0.0f, float pGreen = 0.0f, float pBlue = 0.0f, float pAlpha = 1.0f);
protected:
private:
    GLuint mFBO;
    GLuint mDepthBuffer;
    GLuint mTexture;
};

#endif // FBO_HPP
