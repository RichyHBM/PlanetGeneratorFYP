

#include "TextureRenderer.hpp"

#include <glm/gtx/transform2.hpp>

TextureRenderer::TextureRenderer()
{
    mTexture = 0;
}

void TextureRenderer::Create( float pWidth, float pHeight, bool pInvert )
{
    std::string vertexShader =
        "#version 120\n"
        "uniform mat4 MVP;\n"
        "attribute vec4 Position;\n"
        "attribute vec2 UV;\n"
        "varying vec2 uv;\n"
        "void main(){\n"
        "uv = UV;\n"
        "gl_Position =  MVP * Position;\n"
        "}";
    std::string fragmentShader =
        "#version 120\n"
        "varying vec2 uv;\n"
        "uniform sampler2D Texture;\n"
        "uniform vec4 Color;\n"
        "void main(){\n"
        "vec4 textur = texture2D( Texture, uv ).rgba;\n"
        "textur.rgba += Color.rgba;\n"
        "gl_FragColor = textur;\n"
        "}";
    mShader.LoadShaderCode( vertexShader ,fragmentShader );
    mPosition = glm::vec3( 0.0f );
    mColor = glm::vec4( 0.0f );
    mVertexList.push_back( glm::vec3( 0.0f, 0.0f, 0.0f ) );
    mVertexList.push_back( glm::vec3( 0.0f, pHeight, 0.0f ) );
    mVertexList.push_back( glm::vec3( pWidth, 0.0f, 0.0f ) );
    mVertexList.push_back( glm::vec3( pWidth, 0.0f, 0.0f ) );
    mVertexList.push_back( glm::vec3( 0.0f, pHeight, 0.0f ) );
    mVertexList.push_back( glm::vec3( pWidth, pHeight, 0.0f ) );

    if( pInvert ) {
        mUVList.push_back( glm::vec2( 0.0f , 1.0f ) );
        mUVList.push_back( glm::vec2( 0.0f , 0.0f ) );
        mUVList.push_back( glm::vec2( 1.0f , 1.0f ) );
        mUVList.push_back( glm::vec2( 1.0f , 1.0f ) );
        mUVList.push_back( glm::vec2( 0.0f , 0.0f ) );
        mUVList.push_back( glm::vec2( 1.0f , 0.0f ) );

    } else {
        mUVList.push_back( glm::vec2( 0.0f , 0.0f ) );
        mUVList.push_back( glm::vec2( 0.0f , 1.0f ) );
        mUVList.push_back( glm::vec2( 1.0f , 0.0f ) );
        mUVList.push_back( glm::vec2( 1.0f , 0.0f ) );
        mUVList.push_back( glm::vec2( 0.0f , 1.0f ) );
        mUVList.push_back( glm::vec2( 1.0f , 1.0f ) );
    }

    mVertexBuffer.AddData( mVertexList, sizeof( glm::vec3 ) );
    mUVBuffer.AddData( mUVList, sizeof( glm::vec2 ) );
    mVertexBuffer.SetAttributeIndex( mShader.GetAttribute( "Position" ) );
    mUVBuffer.SetAttributeIndex( mShader.GetAttribute( "UV" ) );
}

TextureRenderer::~TextureRenderer()
{
}


void TextureRenderer::SetPosition( const glm::vec2 &pPosition )
{
    mPosition = glm::vec3( pPosition.x, pPosition.y, 0.0f );

    if( mOrtho != NULL ) {
        mMVP = ( *mOrtho ) * glm::translate( glm::mat4( 1.0f ), mPosition );
    }
}

void TextureRenderer::SetOrtho( glm::mat4 &pOrtho )
{
    mOrtho = &pOrtho;
    mMVP = ( *mOrtho ) * glm::translate( glm::mat4( 1.0f ), mPosition );
}

void TextureRenderer::Draw()
{
    mShader.Bind();
    glUniformMatrix4fv( mShader.GetUniform( "MVP" ), 1, GL_FALSE, &mMVP[0][0] );

    if( mTexture != 0 ) {
        glActiveTexture( GL_TEXTURE0 );
        glBindTexture( GL_TEXTURE_2D, mTexture );
        glUniform1i( mShader.GetUniform( "Texture" ), 0 );
    }

    glUniform4fv( mShader.GetUniform( "Color" ),1 , &mColor[0] );
    mVertexBuffer.Bind( 3 );
    mUVBuffer.Bind( 2 );
    glDrawArrays( GL_TRIANGLES, 0, mVertexList.size() );
    mUVBuffer.Unbind();
    mVertexBuffer.Unbind();
    glBindTexture( GL_TEXTURE_2D, 0 );
    Shader::Unbind();
}


void TextureRenderer::SetColor( float pRed , float pGreen, float pBlue , float pAlpha )
{
    mColor.x = pRed;
    mColor.y = pGreen;
    mColor.z = pBlue;
    mColor.w = pAlpha;
}

void TextureRenderer::SetTexture( const GLuint &pTexture )
{
    mTexture = pTexture;
}
