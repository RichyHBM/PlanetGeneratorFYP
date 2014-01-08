#include "Plane.hpp"

#include "framework/ResourceManager.hpp"

Plane::Plane( const glm::vec3 &center, const glm::vec2 &size, int spacing )
{
    mShader = ResourceManager::GetShader( "Terrain", "./Resources/Terrain.vert" ,"./Resources/Terrain.frag" );
    mTerrainTexture = ResourceManager::GetTexture( "TerrainTextures", "./Resources/Textures.png" );
    int xHalfSize = ( size.x / 2.0f );
    int yHalfSize = ( size.y / 2.0f );

    for( int y = -yHalfSize; y < yHalfSize; y += spacing ) {
        for( int x = -xHalfSize; x < xHalfSize; x += spacing ) {
            float heightA = NoisePP.Generate( center.x + x,		center.z + y ),
                  heightB = NoisePP.Generate( center.x + x + spacing, center.z + y ),
                  heightC = NoisePP.Generate( center.x + x,		center.z + y + spacing ),
                  heightD = NoisePP.Generate( center.x + x + spacing, center.z + y + spacing );
            glm::vec3	p1( center.x + x,		center.y, center.z + y ),
                       p2( center.x + x + spacing,	center.y, center.z + y ),
                       p3( center.x + x,		center.y, center.z + y + spacing ),
                       p4( center.x + x + spacing,	center.y, center.z + y + spacing );
            glm::vec2 tl( 0,0 ),
                tr( 1,0 ),
                bl( 0,1 ),
                br( 1,1 );
            mHeightList.push_back( heightA );
            mHeightList.push_back( heightB );
            mHeightList.push_back( heightC );
            mHeightList.push_back( heightD );
            mVertexList.push_back( p1 );
            mVertexList.push_back( p2 );
            mVertexList.push_back( p3 );
            mVertexList.push_back( p4 );
            mNormalList.push_back( tl );
            mNormalList.push_back( tr );
            mNormalList.push_back( bl );
            mNormalList.push_back( br );
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
    mHeightBuffer.AddVectorData( mHeightList, sizeof( float ) );
    mHeightBuffer.SetAttributeIndex( mShader->GetAttribute( "Height" ) );
    mNormalBuffer.AddVectorData( mNormalList, sizeof( glm::vec2 ) );
    mNormalBuffer.SetAttributeIndex( mShader->GetAttribute( "UV" ) );
    mIndexBuffer.AddVectorData( mIndexList, sizeof( unsigned int ) );
    mIndexBuffer.SetTarget( GL_ELEMENT_ARRAY_BUFFER );
}

Plane::~Plane()
{
}

void Plane::Update()
{
}

void Plane::Draw( const glm::mat4 &MVP )
{
    mShader->Bind();
    glUniformMatrix4fv( mShader->GetUniform( "MVP" ), 1, GL_FALSE, &MVP[0][0] );
    mTerrainTexture->Bind();
    glUniform1i( mShader->GetUniform ( "TerrainTexture" ), 0 );
    mVertexBuffer.Bind( 3 );
    mNormalBuffer.Bind( 2 );
    mHeightBuffer.Bind( 1 );
    mIndexBuffer.Bind();
    glDrawElements( GL_TRIANGLES, mIndexList.size(), GL_UNSIGNED_INT, ( void * )0 );
    mIndexBuffer.Unbind();
    mHeightBuffer.Unbind();
    mNormalBuffer.Unbind();
    mVertexBuffer.Unbind();
    Texture::Unbind();
    Shader::Unbind();
}