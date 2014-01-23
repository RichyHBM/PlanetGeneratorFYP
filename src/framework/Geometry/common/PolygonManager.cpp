#include <glm/gtx/transform2.hpp>

#include "PolygonManager.hpp"

#include "../../ResourceManager.hpp"

PolygonManager::PolygonManager()
{
    mShader = ResourceManager::GetShader( "Icosphere", "./Resources/Icosphere.vert" ,"./Resources/Icosphere.frag" );
    mPositionBuffer.SetAttributeIndex( mShader->GetAttribute( "Position" ) );
}

PolygonManager::~PolygonManager()
{
    mShader = NULL;
}

void PolygonManager::AddQuad( const Quad &q )
{
    mQuads.push_back( q );
}

void PolygonManager::NormalizeVert( glm::vec3 &v )
{
    float length = PLANETSIZE * 2;
    float dist = glm::length( v );
    v.x = v.x * length / dist;
    v.y = v.y * length / dist;
    v.z = v.z * length / dist;
}

int PolygonManager::GetVertexCount()
{
    return mQuads.size() * 2;
}

void PolygonManager::GiveHeight( glm::vec3 &v, float pHeight )
{
    float len = glm::length( v );
    glm::vec3 tmp = ( len + pHeight ) * glm::normalize( v );
    v = tmp;
}

void PolygonManager::Subdivide()
{
    std::vector<Quad> tempQuads;

    for( int i = 0; i < mQuads.size(); i++ ) {
        glm::vec3 A = mQuads[i].GetVerticeA(),
                  B = mQuads[i].GetVerticeB(),
                  C = mQuads[i].GetVerticeC(),
                  D = mQuads[i].GetVerticeD();
        glm::vec3 AB = ( A + B ) / glm::vec3( 2.0 );
        glm::vec3 BC = ( B + C ) / glm::vec3( 2.0 );
        glm::vec3 CD = ( C + D ) / glm::vec3( 2.0 );
        glm::vec3 DA = ( D + A ) / glm::vec3( 2.0 );
        glm::vec3 Middle = ( A + C ) / glm::vec3( 2.0 );
        tempQuads.push_back( Quad( A, AB, Middle, DA ) );
        tempQuads.push_back( Quad( AB, B, BC, Middle ) );
        tempQuads.push_back( Quad( Middle, BC, C, CD ) );
        tempQuads.push_back( Quad( DA, Middle, CD, D ) );
    }

    mQuads = tempQuads;
}

void PolygonManager::Distort( const glm::vec3 &origin, const glm::vec3 &direction )
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

void PolygonManager::Spherify()
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

void PolygonManager::BindData()
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

void PolygonManager::Update()
{
}

void PolygonManager::Draw( const glm::mat4 &MVP )
{
    mShader->Bind();
    glUniformMatrix4fv( mShader->GetUniform( "MVP" ), 1, GL_FALSE, &MVP[0][0] );
    mPositionBuffer.Bind( 3 );
    glDrawArrays ( GL_TRIANGLES, 0, mPositionsList.size() );
    mPositionBuffer.Unbind();
    Texture::Unbind();
    Shader::Unbind();
}
