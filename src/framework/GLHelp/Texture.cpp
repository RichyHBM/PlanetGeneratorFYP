#include "SOIL.h"

#include "./Texture.hpp"

bool Texture::Screenshot( const std::string &filename, int x, int y, int w, int h )
{
    Log.Info( "Taking screenshot: " + filename );
    return 0 != SOIL_save_screenshot (
               filename.c_str(),
               SOIL_SAVE_TYPE_BMP,
               x, y, w, h
           );
}

Texture::Texture()
{
    mTextureID = 0;
}

Texture::~Texture()
{
    glDeleteTextures( 1, &mTextureID );
}

bool Texture::LoadFromFile( const std::string &pFileName )
{
    mWidth = 0;
    mHeight = 0;

    if( mTextureID != 0 ) {
        glDeleteTextures( 1, &mTextureID );
    }

    glGenTextures( 1, &mTextureID );
    glBindTexture( GL_TEXTURE_2D, mTextureID );
    //Load the image data
    unsigned char *image = SOIL_load_image( pFileName.c_str(), &mWidth, &mHeight, 0, SOIL_LOAD_RGBA );

    if( image == NULL ) {
        Log.Error( "Failed to load: " + pFileName );
    }

    Log.Success( "Loaded: " + pFileName );
    //Convert the data to a texture
    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, mWidth, mHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, image );
    //Free the data
    SOIL_free_image_data( image );
    Texture::GenMipmaps();
    Texture::Unbind();
    return true;
}

void Texture::Bind()
{
    glBindTexture( GL_TEXTURE_2D, mTextureID );
}

void Texture::Unbind()
{
    glBindTexture( GL_TEXTURE_2D, 0 );
}

bool Texture::GenMipmaps()
{
    bool result = false;

    //If the graphics card doesnt support genMipMaps then try as an extension
    if( glGenerateMipmap ) {
        glGenerateMipmap( GL_TEXTURE_2D );
        result = true;

    } else if( glGenerateMipmapEXT ) {
        glGenerateMipmapEXT( GL_TEXTURE_2D );
        result = true;
    }

    return result;
}

glm::vec2 Texture::GetSize()
{
    return glm::vec2( mWidth, mHeight );
}
