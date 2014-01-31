#include <glm/gtx/transform2.hpp>

#include "SideManager.hpp"

#include "../Managers/ResourceManager.hpp"
#include "../Noise/NoiseppNoise.hpp"

SideManager::SideManager( const Quad &q ): mInitialQuad( q )
{
    mShader = ResourceManager::GetShader( "Icosphere", "./Resources/Icosphere.vert" ,"./Resources/Icosphere.frag" );
    mPositionBuffer.SetAttributeIndex( mShader->GetAttribute( "Position" ) );
    mNormalBuffer.SetAttributeIndex( mShader->GetAttribute( "Normal" ) );
    mUVBuffer.SetAttributeIndex( mShader->GetAttribute( "UV" ) );
    mTerrainTexture = ResourceManager::GetTexture( "TerrainTextures", "./Resources/Textures.png" );
    mQuads.push_back( mInitialQuad );
}

SideManager::~SideManager()
{
    mShader = NULL;
}

void SideManager::SetNoise( NoiseppNoise *noise )
{
    mNoise = noise;
}

void SideManager::NormalizeVert( glm::vec3 &v )
{
    float length = RuntimeSettings::Settings.PlanetRadius * 2;
    float dist = glm::length( v );
    v.x = v.x * length / dist;
    v.y = v.y * length / dist;
    v.z = v.z * length / dist;
}

int SideManager::GetVertexCount()
{
    return mQuads.size() * 2;
}

std::vector<Quad> SideManager::Subdivide( const Quad &q )
{
    std::vector<Quad> quads;
    glm::vec3 A = q.GetVerticeA(),
              B = q.GetVerticeB(),
              C = q.GetVerticeC(),
              D = q.GetVerticeD();
    glm::vec3 AB = ( A + B ) / glm::vec3( 2.0 );
    glm::vec3 BC = ( B + C ) / glm::vec3( 2.0 );
    glm::vec3 CD = ( C + D ) / glm::vec3( 2.0 );
    glm::vec3 DA = ( D + A ) / glm::vec3( 2.0 );
    glm::vec3 Middle = ( A + C ) / glm::vec3( 2.0 );
    quads.push_back( Quad( A, AB, Middle, DA ) );
    quads.push_back( Quad( AB, B, BC, Middle ) );
    quads.push_back( Quad( Middle, BC, C, CD ) );
    quads.push_back( Quad( DA, Middle, CD, D ) );
    return quads;
}

void SideManager::Distort(  )
{
    for( int i = 0; i < mQuads.size(); i++ ) {
        glm::vec3 pos[4];

        for( int j = 0; j < 4; j++ ) {
            pos[j] = mQuads[i].GetVertice( j );
            float dist = mNoise->Generate( pos[j].x, pos[j].y, pos[j].z ) + 1;
            pos[j] = glm::vec3( dist * glm::vec4( pos[j].x, pos[j].y, pos[j].z, 0 ) );
        }

        mQuads[i] = Quad( pos[0], pos[1], pos[2], pos[3] );
    }
}

void SideManager::Spherify()
{
    for( int i = 0; i < mQuads.size(); i++ ) {
        glm::vec3 A = mQuads[i].GetVerticeA(),
                  B = mQuads[i].GetVerticeB(),
                  C = mQuads[i].GetVerticeC(),
                  D = mQuads[i].GetVerticeD();
        NormalizeVert( A );
        NormalizeVert( B );
        NormalizeVert( C );
        NormalizeVert( D );
        mQuads[i] = Quad( A, B, C, D );
    }
}

void SideManager::BindData()
{
    std::vector<glm::vec3> mPositionsList;
    std::vector<glm::vec3> mNormalsList;
    std::vector<glm::vec2> mUVsList;
    std::vector<unsigned int> mIndices;

    for( int i = 0; i < mQuads.size(); i++ ) {
        mPositionsList.push_back( mQuads[i].GetVerticeA());
        mPositionsList.push_back( mQuads[i].GetVerticeB());
        mPositionsList.push_back( mQuads[i].GetVerticeC());
        mPositionsList.push_back( mQuads[i].GetVerticeD());

        mNormalsList.push_back( mQuads[i].GetNormalA());
        mNormalsList.push_back( mQuads[i].GetNormalB());
        mNormalsList.push_back( mQuads[i].GetNormalC());
        mNormalsList.push_back( mQuads[i].GetNormalD());

        mUVsList.push_back( mQuads[i].GetUVA());
        mUVsList.push_back( mQuads[i].GetUVB());
        mUVsList.push_back( mQuads[i].GetUVC());
        mUVsList.push_back( mQuads[i].GetUVD());
            
        int size = mPositionsList.size();

        mIndices.push_back( size - 4 );
        mIndices.push_back( size - 3 );
        mIndices.push_back( size - 1 );
        mIndices.push_back( size - 1 );
        mIndices.push_back( size - 3 );
        mIndices.push_back( size - 2 );
    }

    mPositionBuffer.AddVectorData( mPositionsList, sizeof( glm::vec3 ) );
    mPositionBuffer.SetAttributeIndex( mShader->GetAttribute( "Position" ) );
    mNormalBuffer.AddVectorData( mNormalsList, sizeof( glm::vec3 ) );
    mNormalBuffer.SetAttributeIndex( mShader->GetAttribute( "Normal" ) );
    mUVBuffer.AddVectorData( mUVsList, sizeof( glm::vec2 ) );
    mUVBuffer.SetAttributeIndex( mShader->GetAttribute( "UV" ) );
    mIndexBuffer.AddVectorData( mIndices, sizeof( unsigned int ) );
    mIndexBuffer.SetTarget( GL_ELEMENT_ARRAY_BUFFER );
}


void SideManager::Update( const Frustrum &frustrum )
{
}

void SideManager::RebuildSide()
{
    mQuads.clear();
    mInitialQuad.SetSize( RuntimeSettings::Settings.PlanetRadius );
    mQuads.push_back( mInitialQuad );

    for( int subd = 0; subd < RuntimeSettings::Settings.Subdivisions; subd++ ) {
        std::vector<Quad> mTempQuads;

        for( int i = 0; i < mQuads.size(); i++ ) {
            std::vector<Quad> subQuads = Subdivide( mQuads[i] );
            mTempQuads.push_back( subQuads[0] );
            mTempQuads.push_back( subQuads[1] );
            mTempQuads.push_back( subQuads[2] );
            mTempQuads.push_back( subQuads[3] );
        }

        mQuads = mTempQuads;
    }

    Spherify();
    Distort( );
    BindData();
}

void SideManager::Draw( const glm::mat4 &MVP, const Frustrum &frustrum )
{
    //If the initial quad isnt in the frustrum then skip the draw
    if( !RuntimeSettings::Settings.DrawHidden )
        if( !frustrum.InFrustrumAndFacing( mInitialQuad ) ) {
            return;
        }

    glm::mat4 NormalMat = glm::transpose( glm::inverse( glm::mat4( 1.0f ) ) );
    mShader->Bind();
    glUniformMatrix4fv( mShader->GetUniform( "MVP" ), 1, GL_FALSE, &MVP[0][0] );
    glUniformMatrix4fv( mShader->GetUniform( "NormalMat" ), 1, GL_FALSE, &NormalMat[0][0] );
    glUniform3fv( mShader->GetUniform( "LightDirection" ), 1, &RuntimeSettings::Settings.LightDirection[0] );
    mTerrainTexture->Bind();
    glUniform1i( mShader->GetUniform ( "Texture" ), 0 );
    mPositionBuffer.Bind( 3 );
    mNormalBuffer.Bind( 3 );
    mUVBuffer.Bind( 2 );
    mIndexBuffer.Bind();
    glDrawElements( GL_TRIANGLES, mQuads.size() * 6, GL_UNSIGNED_INT, ( void * )0 );
    mIndexBuffer.Unbind();
    mUVBuffer.Unbind();
    mNormalBuffer.Unbind();
    mPositionBuffer.Unbind();
    Texture::Unbind();
    Shader::Unbind();
}
