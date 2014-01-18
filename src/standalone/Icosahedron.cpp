#include "./Icosahedron.hpp"

#include <glm/gtx/compatibility.hpp>

#include "framework/MatrixManager.hpp"
#include "framework/Utilities.hpp"

Icosahedron::Icosahedron()
{
    double t = ( PLANETRADIUS + sqrt( 5.0 ) ) / 2.0;
    std::vector<glm::vec3> verticies;
    verticies.push_back( glm::vec3( -PLANETRADIUS,  t,  0 ) );
    verticies.push_back( glm::vec3( PLANETRADIUS,  t,  0 ) );
    verticies.push_back( glm::vec3( -PLANETRADIUS, -t,  0 ) );
    verticies.push_back( glm::vec3( PLANETRADIUS, -t,  0 ) );
    verticies.push_back( glm::vec3( 0, -PLANETRADIUS,  t ) );
    verticies.push_back( glm::vec3( 0,  PLANETRADIUS,  t ) );
    verticies.push_back( glm::vec3( 0, -PLANETRADIUS, -t ) );
    verticies.push_back( glm::vec3( 0,  PLANETRADIUS, -t ) );
    verticies.push_back( glm::vec3( t,  0, -PLANETRADIUS ) );
    verticies.push_back( glm::vec3( t,  0,  PLANETRADIUS ) );
    verticies.push_back( glm::vec3( -t,  0, -PLANETRADIUS ) );
    verticies.push_back( glm::vec3( -t,  0,  PLANETRADIUS ) );
    mTriangMan.AddTriangle( Triangle( verticies[0], verticies[11], verticies[5] ) );
    mTriangMan.AddTriangle( Triangle( verticies[0], verticies[5], verticies[1] ) );
    mTriangMan.AddTriangle( Triangle( verticies[0], verticies[1], verticies[7] ) );
    mTriangMan.AddTriangle( Triangle( verticies[0], verticies[7], verticies[10] ) );
    mTriangMan.AddTriangle( Triangle( verticies[0], verticies[10], verticies[11] ) );
    // 5 adjacent faces
    mTriangMan.AddTriangle( Triangle( verticies[1], verticies[5], verticies[9] ) );
    mTriangMan.AddTriangle( Triangle( verticies[5], verticies[11], verticies[4] ) );
    mTriangMan.AddTriangle( Triangle( verticies[11], verticies[10], verticies[2] ) );
    mTriangMan.AddTriangle( Triangle( verticies[10], verticies[7], verticies[6] ) );
    mTriangMan.AddTriangle( Triangle( verticies[7], verticies[1], verticies[8] ) );
    // 5 faces around point 3
    mTriangMan.AddTriangle( Triangle( verticies[3], verticies[9], verticies[4] ) );
    mTriangMan.AddTriangle( Triangle( verticies[3], verticies[4], verticies[2] ) );
    mTriangMan.AddTriangle( Triangle( verticies[3], verticies[2], verticies[6] ) );
    mTriangMan.AddTriangle( Triangle( verticies[3], verticies[6], verticies[8] ) );
    mTriangMan.AddTriangle( Triangle( verticies[3], verticies[8], verticies[9] ) );
    // 5 adjacent faces
    mTriangMan.AddTriangle( Triangle( verticies[4], verticies[9], verticies[5] ) );
    mTriangMan.AddTriangle( Triangle( verticies[2], verticies[4], verticies[11] ) );
    mTriangMan.AddTriangle( Triangle( verticies[6], verticies[2], verticies[10] ) );
    mTriangMan.AddTriangle( Triangle( verticies[8], verticies[6], verticies[7] ) );
    mTriangMan.AddTriangle( Triangle( verticies[9], verticies[8], verticies[1] ) );

    for( int i = 0; i < 5; i++ ) {
        mTriangMan.Subdivide();
    }

    mTriangMan.BindData();

    for( int i = 0; i < 500; i++ ) {
        float a = ( ( std::rand() % 2001 ) - 1000 ) / 1000.0f ,
              b = ( ( std::rand() % 2001 ) - 1000 ) / 1000.0f,
              c = ( ( std::rand() % 2001 ) - 1000 ) / 1000.0f;
        mTriangMan.Distort( glm::vec3( 0 ),
                            glm::vec3( a , b, c ) );
    }
}

Icosahedron::~Icosahedron()
{
}

void Icosahedron::Update()
{
    mMVP = MatrixControl.PerspectiveView() * glm::mat4( 1.0f );
}

void Icosahedron::Draw()
{
    mTriangMan.Draw( mMVP );
}

glm::vec2 Icosahedron::UV( glm::vec3 pos )
{
    glm::vec2 uv;
    uv.x = 0.5f * ( 1.0f + std::atan2( pos.z , pos.x ) * ( Util::Maths::f1oPI ) );
    uv.y = std::acos( pos.y ) * ( Util::Maths::f1oPI );
    return uv;
}
