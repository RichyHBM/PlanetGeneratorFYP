#ifndef BITMAPTEXT_HPP
#define BITMAPTEXT_HPP

#include "../Includes.hpp"

#include "Texture.hpp"
#include "Shader.hpp"
#include "VBO.hpp"

class BitmapText
{
protected:
    VBO mVertexBuffer;
    VBO mUVBuffer;

    std::vector<GLfloat> mVertexList;
    std::vector<GLfloat> mUVList;

    Texture mBitmap;
    Shader mShader;

    std::vector<glm::vec4> mPositions;
    std::string mText;
    glm::vec4 mColor;

    void Rebuild();
    glm::mat4 mMVP;
    glm::mat4 mOrtho;
    glm::vec3 mPosition;

public:
    ///
    ///Default constructor
    ///
    BitmapText();
    ///
    ///Default destructor
    ///
    ~BitmapText();
    ///
    ///Load text from files
    ///
    void LoadFile( const std::string &pImageFile, const std::string &pUVFile );
    ///
    ///Set the text string
    ///
    void SetText( const std::string &pText );
    ///
    ///Set the 2d position
    ///
    void SetPosition( const glm::vec2 &pPosition );
    ///
    ///Draw to screen
    ///
    void Draw();
    ///
    ///Set the colour/tint
    ///
    void SetColor( float pRed , float pGreen, float pBlue , float pAlpha );
    ///
    ///Set the orhto/2d matrix
    ///
    void SetOrtho( glm::mat4 &pOrtho );
};


#endif // BITMAPTEXT_HPP_INCLUDED
