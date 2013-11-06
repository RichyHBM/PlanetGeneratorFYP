#include "../Utilities.hpp"
#include "FBO.hpp"


FBO::FBO()
{
    glGenRenderbuffersEXT( 1, &mDepthBuffer );
    Util::PrintGLErrors();
    glGenTextures( 1, &mTexture );
    Util::PrintGLErrors();
    glGenFramebuffersEXT( 1, &mFBO );
    Util::PrintGLErrors();
}

FBO::~FBO()
{
    glDeleteFramebuffersEXT( 1, &mFBO );
    Util::PrintGLErrors();
    glDeleteTextures( 1, &mTexture );
    Util::PrintGLErrors();
    glDeleteRenderbuffersEXT( 1, &mDepthBuffer );
    Util::PrintGLErrors();
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
    Util::PrintGLErrors();
    glBindRenderbufferEXT( GL_RENDERBUFFER_EXT, mDepthBuffer );
    Util::PrintGLErrors();
    glRenderbufferStorageEXT( GL_RENDERBUFFER_EXT, GL_DEPTH_COMPONENT, pWidth, pHeight );
    Util::PrintGLErrors();
    glFramebufferRenderbufferEXT( GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_RENDERBUFFER_EXT, mDepthBuffer );
    Util::PrintGLErrors();
    glBindTexture( GL_TEXTURE_2D, mTexture );
    Util::PrintGLErrors();
    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, pWidth, pHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL );
    Util::PrintGLErrors();
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
    Util::PrintGLErrors();
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
    Util::PrintGLErrors();
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    Util::PrintGLErrors();
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    Util::PrintGLErrors();
    glBindTexture( GL_TEXTURE_2D, 0 );
    Util::PrintGLErrors();
    glFramebufferTexture2DEXT( GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, mTexture, 0 );
    Util::PrintGLErrors();
    glFramebufferRenderbufferEXT( GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_RENDERBUFFER_EXT, mDepthBuffer );
    Util::PrintGLErrors();
    GLenum status = glCheckFramebufferStatusEXT( GL_FRAMEBUFFER_EXT );
    Util::PrintGLErrors();

    if ( status != GL_FRAMEBUFFER_COMPLETE_EXT ) {
        Log.Error( "Couldn't create frame buffer" );
        glBindFramebufferEXT( GL_FRAMEBUFFER_EXT, 0 );
        Util::PrintGLErrors();
        return false;
    }

    glBindRenderbufferEXT( GL_RENDERBUFFER_EXT, 0 );
    Util::PrintGLErrors();
    glBindFramebufferEXT( GL_FRAMEBUFFER_EXT, 0 );
    Util::PrintGLErrors();
    return true;
}

void FBO::Bind()
{
    glBindFramebufferEXT( GL_FRAMEBUFFER_EXT, mFBO );
    Util::PrintGLErrors();
}

void FBO::Unbind()
{
    glBindFramebufferEXT( GL_FRAMEBUFFER_EXT, 0 );
    Util::PrintGLErrors();
}

void FBO::Clear( float pRed, float pGreen, float pBlue, float pAlpha )
{
    glBindFramebufferEXT( GL_FRAMEBUFFER_EXT, mFBO );
    Util::PrintGLErrors();
    glClearColor( pRed, pGreen, pBlue, pAlpha );
    Util::PrintGLErrors();
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    Util::PrintGLErrors();
}
