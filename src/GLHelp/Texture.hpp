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
    ///
    ///Default constructor
    ///
    Texture();
    ///
    ///Default destructor
    ///
    ~Texture();
    ///
    ///Load texture from a file
    ///
    bool LoadFromFile(const std::string &pFileName);
    ///
    ///Get the textures size
    ///
    glm::vec2 GetSize();
    ///
    ///Bind the texture
    ///
    void Bind();
    ///
    ///Unbind any texture
    ///
    static void Unbind();
    ///
    ///Take a screenshot of the current openGL context
    ///
    static bool Screenshot(const std::string &filename, int x, int y, int w, int h );
};

#endif // TEXTURE_HPP_INCLUDED
