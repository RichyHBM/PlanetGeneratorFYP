#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include "../Includes.hpp"

#include <string>

class Texture
{
protected:
    int mWidth, mHeight;
    GLuint mTextureID;
public:
    Texture();
    ~Texture();
    bool LoadFromFile( const std::string &pFileName );
    bool LoadData( unsigned char *image, int Width, int Height );
    glm::vec2 GetSize();
    void Bind();
    static void Unbind();

    GLuint GetGLUINT();

    //Generate mipmaps performing safety check
    static bool GenMipmaps();

    //Take a screen shot of the current openGL context
    static bool Screenshot( const std::string &filename, int x, int y, int w, int h );
};

#endif // TEXTURE_HPP_INCLUDED
