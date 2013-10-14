#ifndef BITMAPTEXT_HPP
#define BITMAPTEXT_HPP

#include "../Includes.hpp"

#include "Texture.hpp"
#include "Shader.hpp"
#include "VBO.hpp"

//Class to draw text to screen, must have font bitmap and font positioning information as files
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
    BitmapText();
    ~BitmapText();
    
	//Load text from files
    void LoadFile( const std::string &pImageFile, const std::string &pUVFile );
    
    void SetText( const std::string &pText );
	void SetPosition( const glm::vec3 &pPosition );
    void SetPosition( const glm::vec2 &pPosition );
    void Draw();
	
	//Set the color/tint
    void SetColor( float pRed , float pGreen, float pBlue , float pAlpha );
	
	//Set the orhto/2d matrix
    void SetOrtho( glm::mat4 &pOrtho );
};


#endif // BITMAPTEXT_HPP_INCLUDED
