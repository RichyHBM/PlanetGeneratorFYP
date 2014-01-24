#include <glm/gtx/transform2.hpp>

#include "SideManager.hpp"

#include "../ResourceManager.hpp"

SideManager::SideManager(const Quad& q): mInitialQuad(q)
{
    mShader = ResourceManager::GetShader( "Icosphere", "./Resources/Icosphere.vert" ,"./Resources/Icosphere.frag" );
    mPositionBuffer.SetAttributeIndex( mShader->GetAttribute( "Position" ) );
    mQuads.push_back(mInitialQuad);
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

std::vector<Quad> SideManager::Subdivide(const Quad& q)
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

    quads.push_back( Quad( A, AB, Middle, DA ));
    quads.push_back( Quad( AB, B, BC, Middle ));
    quads.push_back( Quad( Middle, BC, C, CD ));
    quads.push_back( Quad( DA, Middle, CD, D ));

    return quads;
}

void SideManager::Distort( const glm::vec3 &origin, const glm::vec3 &direction )
{
    glm::vec3 n = direction - origin;
    float diff = 0.001f;
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
    mPositionsList.clear();

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
    }

    mPositionBuffer.AddVectorData( mPositionsList, sizeof( glm::vec3 ) );
    mPositionBuffer.SetAttributeIndex( mShader->GetAttribute( "Position" ) );
}

void SideManager::Update(const Frustrum& frustrum)
{
    mQuads.clear();
    mInitialQuad.SetSize(RuntimeSettings::Settings.PlanetRadius);
    mQuads.push_back(mInitialQuad);

    for(int subd = 0; subd < RuntimeSettings::Settings.Subdivisions; subd++)
    {
        std::vector<Quad> mTempQuads;
        for(int i = 0; i < mQuads.size(); i++)
        {
            if(frustrum.InFrustrumAndFacing(mQuads[i]))
            {
                std::vector<Quad> subQuads = Subdivide(mQuads[i]);
                mTempQuads.push_back(subQuads[0]);
                mTempQuads.push_back(subQuads[1]);
                mTempQuads.push_back(subQuads[2]);
                mTempQuads.push_back(subQuads[3]);
            }
            else{
                mTempQuads.push_back(mQuads[i]);
            }
        }
        mQuads = mTempQuads;
    }

    Spherify();

    BindData();
}

void SideManager::Draw( const glm::mat4 &MVP )
{
    mShader->Bind();
    glUniformMatrix4fv( mShader->GetUniform( "MVP" ), 1, GL_FALSE, &MVP[0][0] );
    mPositionBuffer.Bind( 3 );
    glDrawArrays ( GL_TRIANGLES, 0, mPositionsList.size() );
    mPositionBuffer.Unbind();
    Texture::Unbind();
    Shader::Unbind();
}
