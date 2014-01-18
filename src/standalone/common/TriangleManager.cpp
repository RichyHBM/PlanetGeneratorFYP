#include <glm/gtx/transform2.hpp>

#include "TriangleManager.hpp"

#include "framework/ResourceManager.hpp"

TriangleManager::TriangleManager()
{
    mShader = ResourceManager::GetShader( "Icosphere", "./Resources/Icosphere.vert" ,"./Resources/Icosphere.frag" );
    mPositionBuffer.SetAttributeIndex( mShader->GetAttribute( "Position" ) );
}

TriangleManager::~TriangleManager()
{
    mShader = NULL;
}

void TriangleManager::AddTriangle( const Triangle &t )
{
    mTriangles.push_back( t );
}

/*void TriangleManager::Undivide()
{
    std::vector<Triangle> tempTriangles;
    for(int i = 0; i < mTriangles.size(); i+= 4)
    {
        glm::vec3 a = mTriangles[i].GetVerticeC();

        glm::vec3 b = mTriangles[i+3].GetVerticeB();
        glm::vec3 c = mTriangles[i+2].GetVerticeC();
        tempTriangles.push_back(Triangle(a,b,c,mTriangles[i].GetLevel() -1));
    }
    mTriangles = tempTriangles;
}
*/

void TriangleManager::NormalizeVert( glm::vec3 &v )
{
    float length = PLANETRADIUS * 2;
    float dist = glm::length( v );
    v.x = v.x * length / dist;
    v.y = v.y * length / dist;
    v.z = v.z * length / dist;
}

void TriangleManager::Normalize()
{
    for( int i = 0; i < mTriangles.size(); i++ ) {
        glm::vec3 &A = mTriangles[i].GetVerticeA(),
                   &B = mTriangles[i].GetVerticeB(),
                    &C = mTriangles[i].GetVerticeC();
        NormalizeVert( A );
        NormalizeVert( B );
        NormalizeVert( C );
    }
}

void TriangleManager::GiveHeight( glm::vec3 &v, float pHeight )
{
    float len = glm::length( v );
    glm::vec3 tmp = ( len + pHeight ) * glm::normalize( v );
    v = tmp;
}

void TriangleManager::Subdivide()
{
    std::vector<Triangle> tempTriangles;

    for( int i = 0; i < mTriangles.size(); i++ ) {
        glm::vec3 A = mTriangles[i].GetVerticeA(),
                  B = mTriangles[i].GetVerticeB(),
                  C = mTriangles[i].GetVerticeC();
        glm::vec3 AB = ( A + B ) / glm::vec3( 2.0 );
        glm::vec3 BC = ( B + C ) / glm::vec3( 2.0 );
        glm::vec3 CA = ( C + A ) / glm::vec3( 2.0 );
        tempTriangles.push_back( Triangle( AB,BC,A ) );
        tempTriangles.push_back( Triangle( CA,A,BC ) );
        tempTriangles.push_back( Triangle( CA,BC,C ) );
        tempTriangles.push_back( Triangle( AB,B,BC ) );
    }

    mTriangles = tempTriangles;
    Normalize();
}

void TriangleManager::Distort( const glm::vec3 &origin, const glm::vec3 &direction )
{
    glm::vec3 n = direction - origin;
    float diff = 0.001f;
    glm::mat4 min = glm::scale( glm::mat4( 1.0f ), glm::vec3( 1.0f - diff ) );
    glm::mat4 max = glm::scale( glm::mat4( 1.0f ),glm::vec3( 1.0f + diff ) );

    for( int i = 0; i < mPositionsList.size(); i++ ) {
        glm::vec3 toOrigin = mPositionsList[i] - origin;
        float d = glm::dot( n, toOrigin );

        if( d > 0.0f ) {
            mPositionsList[i] = glm::vec3(
                                    min *
                                    glm::vec4( mPositionsList[i].x, mPositionsList[i].y, mPositionsList[i].z, 1.0f )
                                );

        } else {
            mPositionsList[i] = glm::vec3(
                                    max *
                                    glm::vec4( mPositionsList[i].x, mPositionsList[i].y, mPositionsList[i].z, 1.0f )
                                );
        }
    }

    mPositionBuffer.AddVectorData( mPositionsList, sizeof( glm::vec3 ) );
    mPositionBuffer.SetAttributeIndex( mShader->GetAttribute( "Position" ) );
}

void TriangleManager::BindData()
{
    mPositionsList.clear();

    for( int i = 0; i < mTriangles.size(); i++ ) {
        glm::vec3 A = mTriangles[i].GetVerticeA(), B = mTriangles[i].GetVerticeB(), C = mTriangles[i].GetVerticeC();
        mPositionsList.push_back( mTriangles[i].GetVerticeA() );
        mPositionsList.push_back( mTriangles[i].GetVerticeB() );
        mPositionsList.push_back( mTriangles[i].GetVerticeC() );
    }

    mPositionBuffer.AddVectorData( mPositionsList, sizeof( glm::vec3 ) );
    mPositionBuffer.SetAttributeIndex( mShader->GetAttribute( "Position" ) );
}

void TriangleManager::Draw( const glm::mat4 &MVP )
{
    mShader->Bind();
    glUniformMatrix4fv( mShader->GetUniform( "MVP" ), 1, GL_FALSE, &MVP[0][0] );
    mPositionBuffer.Bind( 3 );
    glDrawArrays ( GL_TRIANGLES, 0, mPositionsList.size() );
    mPositionBuffer.Unbind();
    Texture::Unbind();
    Shader::Unbind();
}
