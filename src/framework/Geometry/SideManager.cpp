#include <glm/gtx/transform2.hpp>

#include "SideManager.hpp"

#include "../Managers/ResourceManager.hpp"

SideManager::SideManager( const Quad &q ): mInitialQuad( q )
{
    mShader = ResourceManager::GetShader( "Icosphere", "./Resources/Icosphere.vert" ,"./Resources/Icosphere.frag" );
    mPositionBuffer.SetAttributeIndex( mShader->GetAttribute( "Position" ) );
    mNormalBuffer.SetAttributeIndex( mShader->GetAttribute( "Normal" ) );
    mQuads.push_back( mInitialQuad );
}

SideManager::~SideManager()
{
    mShader = NULL;
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

void SideManager::Distort( const glm::vec3 &origin, const glm::vec3 &direction )
{
    glm::vec3 n = direction - origin;
    float diff = RuntimeSettings::Settings.DistortionSize * 0.001f;
    glm::mat4 min = glm::scale( glm::mat4( 1.0f ), glm::vec3( 1.0f - diff ) );
    glm::mat4 max = glm::scale( glm::mat4( 1.0f ),glm::vec3( 1.0f + diff ) );

    for( int i = 0; i < mQuads.size(); i++ ) {
        glm::vec3 pos[4];

        for( int j = 0; j < 4; j++ ) {
            pos[j] = mQuads[i].GetVertice( j );
            glm::vec3 toOrigin = pos[j] - origin;
            float d = glm::dot( n, toOrigin );

            if( d > 0.0f ) {
                pos[j] = glm::vec3( min * glm::vec4( pos[j].x, pos[j].y, pos[j].z, 0 ) );

            } else {
                pos[j] = glm::vec3( max * glm::vec4( pos[j].x, pos[j].y, pos[j].z, 0 ) );
            }
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

    for( int i = 0; i < mQuads.size(); i++ ) {
        glm::vec3 A = mQuads[i].GetVerticeA(),
                  B = mQuads[i].GetVerticeB(),
                  C = mQuads[i].GetVerticeC(),
                  D = mQuads[i].GetVerticeD();
        mPositionsList.push_back( A );
        mPositionsList.push_back( B );
        mPositionsList.push_back( D );
        mPositionsList.push_back( D );
        mPositionsList.push_back( B );
        mPositionsList.push_back( C );
        glm::vec3 Anorm = mQuads[i].GetVerticeA(),
                  Bnorm = mQuads[i].GetVerticeB(),
                  Cnorm = mQuads[i].GetVerticeC(),
                  Dnorm = mQuads[i].GetVerticeD();
        mNormalsList.push_back( A );
        mNormalsList.push_back( B );
        mNormalsList.push_back( D );
        mNormalsList.push_back( D );
        mNormalsList.push_back( B );
        mNormalsList.push_back( C );
    }

    mPositionBuffer.AddVectorData( mPositionsList, sizeof( glm::vec3 ) );
    mPositionBuffer.SetAttributeIndex( mShader->GetAttribute( "Position" ) );
    mNormalBuffer.AddVectorData( mNormalsList, sizeof( glm::vec3 ) );
    mNormalBuffer.SetAttributeIndex( mShader->GetAttribute( "Normal" ) );
}

void SideManager::RebuildDistortions()
{
    mDistortionPlanes.clear();
    std::srand( RuntimeSettings::Settings.Seed );

    for( int i = 0; i < RuntimeSettings::Settings.Distortions; i++ ) {
        DistortionPlane dist;
        //Allow up to 4 decimal points random
        float a = ( ( std::rand() % 2001 ) - 1000 ) / 1000.0f ,
              b = ( ( std::rand() % 2001 ) - 1000 ) / 1000.0f,
              c = ( ( std::rand() % 2001 ) - 1000 ) / 1000.0f;
        dist.Direction = glm::vec3( a , b, c );
        int pr = RuntimeSettings::Settings.PlanetRadius;
        a = ( ( std::rand() % ( ( pr * 2 ) + 1 ) ) - pr );
        b = ( ( std::rand() % ( ( pr * 2 ) + 1 ) ) - pr );
        c = ( ( std::rand() % ( ( pr * 2 ) + 1 ) ) - pr );
        dist.Origin = glm::vec3( a , b, c );
        mDistortionPlanes.push_back( dist );
    }
}

void SideManager::Update( const Frustrum &frustrum )
{
    if( RuntimeSettings::Settings.RealtimeRebuild ) {
        mQuads.clear();
        mInitialQuad.SetSize( RuntimeSettings::Settings.PlanetRadius );
        mQuads.push_back( mInitialQuad );

        for( int subd = 0; subd < RuntimeSettings::Settings.Subdivisions; subd++ ) {
            std::vector<Quad> mTempQuads;

            for( int i = 0; i < mQuads.size(); i++ ) {
                if( frustrum.InFrustrumAndFacing( mQuads[i] ) ) {
                    std::vector<Quad> subQuads = Subdivide( mQuads[i] );
                    mTempQuads.push_back( subQuads[0] );
                    mTempQuads.push_back( subQuads[1] );
                    mTempQuads.push_back( subQuads[2] );
                    mTempQuads.push_back( subQuads[3] );

                } else {
                    mTempQuads.push_back( mQuads[i] );
                }
            }

            mQuads = mTempQuads;
        }

        Spherify();

        for( int i = 0; i < mDistortionPlanes.size(); i++ ) {
            Distort( mDistortionPlanes[i].Origin, mDistortionPlanes[i].Direction );
        }

        BindData();
    }
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

    for( int i = 0; i < mDistortionPlanes.size(); i++ ) {
        Distort( mDistortionPlanes[i].Origin, mDistortionPlanes[i].Direction );
    }

    BindData();
}

void SideManager::Draw( const glm::mat4 &MVP, const Frustrum &frustrum )
{
    //If the initial quad isnt in the frustrum then skip the draw
    if(!RuntimeSettings::Settings.DrawHidden)
        if( !frustrum.InFrustrumAndFacing( mInitialQuad ) )
            return;

    glm::mat4 NormalMat = glm::transpose( glm::inverse( glm::mat4( 1.0f ) ) );
    mShader->Bind();
    glUniformMatrix4fv( mShader->GetUniform( "MVP" ), 1, GL_FALSE, &MVP[0][0] );
    glUniformMatrix4fv( mShader->GetUniform( "NormalMat" ), 1, GL_FALSE, &NormalMat[0][0] );
    glUniform3fv( mShader->GetUniform( "LightDirection" ), 1, &RuntimeSettings::Settings.LightDirection[0] );
    mPositionBuffer.Bind( 3 );
    mNormalBuffer.Bind( 3 );
    glDrawArrays ( GL_TRIANGLES, 0, mQuads.size() * 6 );
    mNormalBuffer.Unbind();
    mPositionBuffer.Unbind();
    Texture::Unbind();
    Shader::Unbind();
}
