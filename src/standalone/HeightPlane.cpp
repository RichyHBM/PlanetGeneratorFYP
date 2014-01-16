#include "HeightPlane.hpp"

#include "framework/ResourceManager.hpp"

HeightPlane::HeightPlane( const glm::vec3 &center, const glm::vec2 &size, int spacing )
{
    mShader = ResourceManager::GetShader( "NormalTerrain", "./Resources/Terrain.vert" ,"./Resources/Terrain.frag" );
    mTerrainTexture = ResourceManager::GetTexture( "TerrainTextures", "./Resources/Textures.png" );
    mTerrainTexture->Bind();
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
    Texture::Unbind();
    int xHalfSize = ( size.x / 2.0f );
    int yHalfSize = ( size.y / 2.0f );

    for( int y = -yHalfSize; y < yHalfSize; y += spacing ) {
        for( int x = -xHalfSize; x < xHalfSize; x += spacing ) {
            float heightA = NoisePP.Generate( x, y ),
                  heightB = NoisePP.Generate( x + 1, y ),
                  heightC = NoisePP.Generate( x, y + 1 ),
                  heightD = NoisePP.Generate( x + 1, y + 1 );
            glm::vec3  p1( center.x + x, center.y, center.z + y ),
                p2( center.x + x + spacing, center.y, center.z + y ),
                p3( center.x + x, center.y, center.z + y + spacing ),
                p4( center.x + x + spacing, center.y, center.z + y + spacing );
            glm::vec2 tl( 0,0 ),
                tr( 1,0 ),
                bl( 0,1 ),
                br( 1,1 );
            mVertexList.push_back( p1 );
            mVertexList.push_back( p2 );
            mVertexList.push_back( p3 );
            mVertexList.push_back( p4 );
            mHeightList.push_back( heightA );
            mHeightList.push_back( heightB );
            mHeightList.push_back( heightC );
            mHeightList.push_back( heightD );
            mTexCoordList.push_back( tl );
            mTexCoordList.push_back( tr );
            mTexCoordList.push_back( bl );
            mTexCoordList.push_back( br );
            int size = mVertexList.size();
            mIndexList.push_back( size - 4 );
            mIndexList.push_back( size - 2 );
            mIndexList.push_back( size - 3 );
            mIndexList.push_back( size - 3 );
            mIndexList.push_back( size - 2 );
            mIndexList.push_back( size - 1 );
        }
    }

    mVertexBuffer.AddVectorData( mVertexList, sizeof( glm::vec3 ) );
    mVertexBuffer.SetAttributeIndex( mShader->GetAttribute( "Position" ) );
    mTexCoordBuffer.AddVectorData( mTexCoordList, sizeof( glm::vec2 ) );
    mTexCoordBuffer.SetAttributeIndex( mShader->GetAttribute( "UV" ) );
    mHeightBuffer.AddVectorData( mHeightList, sizeof( float ) );
    mHeightBuffer.SetAttributeIndex( mShader->GetAttribute( "Height" ) );
    mIndexBuffer.AddVectorData( mIndexList, sizeof( unsigned int ) );
    mIndexBuffer.SetTarget( GL_ELEMENT_ARRAY_BUFFER );
}

HeightPlane::~HeightPlane()
{
}

void HeightPlane::Update()
{
}

void HeightPlane::Draw( const glm::mat4 &MVP )
{
    mShader->Bind();
    glUniformMatrix4fv( mShader->GetUniform( "MVP" ), 1, GL_FALSE, &MVP[0][0] );
    mTerrainTexture->Bind();
    glUniform1i( mShader->GetUniform ( "TerrainTexture" ), 0 );
    mVertexBuffer.Bind( 3 );
    mTexCoordBuffer.Bind( 2 );
    mHeightBuffer.Bind( 1 );
    mIndexBuffer.Bind();
    glDrawElements( GL_TRIANGLES, mIndexList.size(), GL_UNSIGNED_INT, ( void * )0 );
    mIndexBuffer.Unbind();
    mHeightBuffer.Unbind();
    mTexCoordBuffer.Unbind();
    mVertexBuffer.Unbind();
    Texture::Unbind();
    Shader::Unbind();
}
