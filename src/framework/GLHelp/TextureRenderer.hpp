#ifndef TEXTURERENDERER_HPP
#define TEXTURERENDERER_HPP

#include "../Includes.hpp"

#include "Shader.hpp"
#include "VBO.hpp"

//Class to handle the rendering of a texture onto the screen

class TextureRenderer
{
protected:
    VBO mVertexBuffer;
    VBO mUVBuffer;

    std::vector<glm::vec3> mVertexList;
    std::vector<glm::vec2> mUVList;

    Shader mShader;

    glm::vec3 mPosition;
    glm::vec4 mColor;

    glm::mat4 *mOrtho;
    glm::mat4 mMVP;

    GLuint mTexture;

public:
    TextureRenderer();
    ~TextureRenderer();

    //Create a new render texture drawer of the given size
    void Create( float pWidth, float pHeight, bool pInvert = false );

    //Set the position of the render target
    void SetPosition( const glm::vec3 &pPosition );
    void SetPosition( const glm::vec2 &pPosition );

    void Draw();
    void SetColor( float pRed , float pGreen, float pBlue , float pAlpha );

    //Set the 2d matrix
    void SetOrtho( glm::mat4 &pOrtho );
    void SetTexture( const GLuint &pTexture );
};

#endif // TEXTURERENDERER_HPP_INCLUDED
