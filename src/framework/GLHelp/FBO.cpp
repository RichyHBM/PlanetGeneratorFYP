#include "../Utilities.hpp"
#include "FBO.hpp"

FBO::FBO()
{
    glGenRenderbuffersEXT( 1, &mDepthBuffer );
    glGenTextures( 1, &mTexture );
    glGenFramebuffersEXT( 1, &mFBO );
}

FBO::~FBO()
{
    glDeleteFramebuffersEXT( 1, &mFBO );
    glDeleteTextures( 1, &mTexture );
    glDeleteRenderbuffersEXT( 1, &mDepthBuffer );
}

GLuint FBO::GetFBO()
{
    return mFBO;
}

GLuint FBO::GetDepthBuffer()
{
    return mDepthBuffer;
}

GLuint FBO::GetTexture()
{
    return mTexture;
}

bool FBO::Create( int pWidth, int pHeight )
{
    glBindFramebufferEXT( GL_FRAMEBUFFER_EXT, mFBO );
    glBindRenderbufferEXT( GL_RENDERBUFFER_EXT, mDepthBuffer );
    glRenderbufferStorageEXT( GL_RENDERBUFFER_EXT, GL_DEPTH_COMPONENT, pWidth, pHeight );
    glFramebufferRenderbufferEXT( GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_RENDERBUFFER_EXT, mDepthBuffer );
    glBindTexture( GL_TEXTURE_2D, mTexture );
    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, pWidth, pHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glBindTexture( GL_TEXTURE_2D, 0 );
    glFramebufferTexture2DEXT( GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, mTexture, 0 );
    glFramebufferRenderbufferEXT( GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_RENDERBUFFER_EXT, mDepthBuffer );
    GLenum status = glCheckFramebufferStatusEXT( GL_FRAMEBUFFER_EXT );

    if ( status != GL_FRAMEBUFFER_COMPLETE_EXT ) {
        std::cout << "Couldn't create frame buffer" << std::endl;
        glBindFramebufferEXT( GL_FRAMEBUFFER_EXT, 0 );
        return false;
    }

    glBindRenderbufferEXT( GL_RENDERBUFFER_EXT, 0 );
    glBindFramebufferEXT( GL_FRAMEBUFFER_EXT, 0 );
    Util::PrintGLErrors();
    return true;
}

void FBO::Bind()
{
    glBindFramebufferEXT( GL_FRAMEBUFFER_EXT, mFBO );
}

void FBO::Unbind()
{
    glBindFramebufferEXT( GL_FRAMEBUFFER_EXT, 0 );
}

void FBO::Clear( float pRed, float pGreen, float pBlue, float pAlpha )
{
    glBindFramebufferEXT( GL_FRAMEBUFFER_EXT, mFBO );
    glClearColor( pRed, pGreen, pBlue, pAlpha );
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
}
