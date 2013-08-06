#ifndef TEXTURERENDERER_HPP
#define TEXTURERENDERER_HPP

#include "../Includes.hpp"

#include "Shader.hpp"
#include "VBO.hpp"

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
    ///
    ///Default constructor
    ///
    TextureRenderer();
    ///
    ///Default destructor
    ///
    ~TextureRenderer();

    ///
    ///Create a new render texture drawer of the given size
    ///
    void Create( float pWidth, float pHeight, bool pInvert = false );
    ///
    ///Set the 2d position of hte render target
    ///
    void SetPosition( const glm::vec2 &pPosition );
    ///
    ///Draw it to screen
    ///
    void Draw();
    ///
    ///Set the colour
    ///
    void SetColor( float pRed , float pGreen, float pBlue , float pAlpha );
    ///
    ///Set the 2d matrix
    ///
    void SetOrtho( glm::mat4 &pOrtho );
    ///
    ///Set the texture
    ///
    void SetTexture( const GLuint &pTexture );
};

#endif // TEXTURERENDERER_HPP_INCLUDED
