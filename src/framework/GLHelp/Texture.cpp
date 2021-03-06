#include "SOIL.h"
#include "../Utilities.hpp"
#include "./Texture.hpp"

bool Texture::Screenshot( const std::string &filename, int x, int y, int w, int h )
{
    Log.Info( "Taking screenshot: " + filename );
    int r = SOIL_save_screenshot (
                filename.c_str(),
                SOIL_SAVE_TYPE_BMP,
                x, y, w, h
            );
    Util::PrintGLErrors();
    return 0 != r;
}

Texture::Texture()
{
    mTextureID = 0;
}

Texture::~Texture()
{
    glDeleteTextures( 1, &mTextureID );
    Util::PrintGLErrors();
}

bool Texture::LoadFromFile( const std::string &pFileName )
{
    mWidth = 0;
    mHeight = 0;

    if( mTextureID != 0 ) {
        glDeleteTextures( 1, &mTextureID );
        Util::PrintGLErrors();
    }

    glGenTextures( 1, &mTextureID );
    Util::PrintGLErrors();
    glBindTexture( GL_TEXTURE_2D, mTextureID );
    Util::PrintGLErrors();
    //Load the image data
    unsigned char *image = SOIL_load_image( pFileName.c_str(), &mWidth, &mHeight, 0, SOIL_LOAD_RGBA );
    Util::PrintGLErrors();

    if( image == NULL ) {
        Log.Error( "Failed to load: " + pFileName );
    }

    Log.Success( "Loaded: " + pFileName );
    //Convert the data to a texture
    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, mWidth, mHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, image );
    Util::PrintGLErrors();
    //Free the data
    SOIL_free_image_data( image );
    Util::PrintGLErrors();
    Texture::GenMipmaps();
    Texture::Unbind();
    return true;
}

bool Texture::LoadData( unsigned char *image, int Width, int Height )
{
    mWidth = Width;
    mHeight = Height;

    if( mTextureID != 0 ) {
        glDeleteTextures( 1, &mTextureID );
        Util::PrintGLErrors();
    }

    glGenTextures( 1, &mTextureID );
    Util::PrintGLErrors();
    glBindTexture( GL_TEXTURE_2D, mTextureID );
    Util::PrintGLErrors();
    //Convert the data to a texture
    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, mWidth, mHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, image );
    Util::PrintGLErrors();
    Texture::GenMipmaps();
    Texture::Unbind();
    return true;
}

void Texture::Bind()
{
    glBindTexture( GL_TEXTURE_2D, mTextureID );
    Util::PrintGLErrors();
}

GLuint Texture::GetGLUINT()
{
    return mTextureID;
}

void Texture::Unbind()
{
    glBindTexture( GL_TEXTURE_2D, 0 );
    Util::PrintGLErrors();
    glActiveTexture( GL_TEXTURE0 );
    Util::PrintGLErrors();
}

bool Texture::GenMipmaps()
{
    //If the graphics card doesnt support genMipMaps then try as an extension
    if( glGenerateMipmap ) {
        glGenerateMipmap( GL_TEXTURE_2D );
        Util::PrintGLErrors();
        return true;

    } else if( glGenerateMipmapEXT ) {
        glGenerateMipmapEXT( GL_TEXTURE_2D );
        Util::PrintGLErrors();
        return true;
    }

    return false;
}

glm::vec2 Texture::GetSize()
{
    return glm::vec2( mWidth, mHeight );
}
