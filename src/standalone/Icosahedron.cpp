#include "./Icosahedron.hpp"

#include <glm/gtx/compatibility.hpp>

#include "framework/MatrixManager.hpp"
#include "framework/Utilities.hpp"
#include "framework/RuntimeSettings.hpp"


Icosahedron::Icosahedron()
{
    float PlanetRadius = RuntimeSettings::Settings.PlanetRadius;
    mPolMan.AddQuad( Quad(
                         glm::vec3( -PlanetRadius,  PlanetRadius, PlanetRadius ),
                         glm::vec3( -PlanetRadius, -PlanetRadius, PlanetRadius ),
                         glm::vec3(  PlanetRadius, -PlanetRadius, PlanetRadius ),
                         glm::vec3(  PlanetRadius,  PlanetRadius, PlanetRadius ) ) );
    mPolMan.AddQuad( Quad(
                         glm::vec3( PlanetRadius,  PlanetRadius, PlanetRadius ),
                         glm::vec3( PlanetRadius, -PlanetRadius, PlanetRadius ),
                         glm::vec3( PlanetRadius, -PlanetRadius,-PlanetRadius ),
                         glm::vec3( PlanetRadius,  PlanetRadius,-PlanetRadius ) ) );
    mPolMan.AddQuad( Quad(
                         glm::vec3( PlanetRadius,  PlanetRadius, -PlanetRadius ),
                         glm::vec3( PlanetRadius, -PlanetRadius, -PlanetRadius ),
                         glm::vec3( -PlanetRadius, -PlanetRadius, -PlanetRadius ),
                         glm::vec3( -PlanetRadius,  PlanetRadius, -PlanetRadius ) ) );
    mPolMan.AddQuad( Quad(
                         glm::vec3( -PlanetRadius,  PlanetRadius, -PlanetRadius ),
                         glm::vec3( -PlanetRadius, -PlanetRadius, -PlanetRadius ),
                         glm::vec3( -PlanetRadius, -PlanetRadius,  PlanetRadius ),
                         glm::vec3( -PlanetRadius,  PlanetRadius,  PlanetRadius ) ) );
    mPolMan.AddQuad( Quad(
                         glm::vec3( -PlanetRadius,  PlanetRadius, -PlanetRadius ),
                         glm::vec3( -PlanetRadius,  PlanetRadius,  PlanetRadius ),
                         glm::vec3(  PlanetRadius,  PlanetRadius, PlanetRadius ),
                         glm::vec3(  PlanetRadius,  PlanetRadius,  -PlanetRadius ) ) );
    mPolMan.AddQuad( Quad(
                         glm::vec3( -PlanetRadius, -PlanetRadius,  PlanetRadius ),
                         glm::vec3( -PlanetRadius, -PlanetRadius, -PlanetRadius ),
                         glm::vec3(  PlanetRadius, -PlanetRadius, -PlanetRadius ),
                         glm::vec3(  PlanetRadius, -PlanetRadius,  PlanetRadius ) ) );

    for( int i = 0; i < RuntimeSettings::Settings.Subdivisions; i++ ) {
        mPolMan.Subdivide();
    }

    mPolMan.Spherify();

    for( int i = 0; i < RuntimeSettings::Settings.Distortions; i++ ) {
        float a = ( ( std::rand() % 2001 ) - 1000 ) / 1000.0f ,
              b = ( ( std::rand() % 2001 ) - 1000 ) / 1000.0f,
              c = ( ( std::rand() % 2001 ) - 1000 ) / 1000.0f;
        mPolMan.Distort( glm::vec3( 0 ),
                         glm::vec3( a , b, c ) );
    }

    mPolMan.BindData();
}

Icosahedron::~Icosahedron()
{
}

int Icosahedron::GetVertexCount()
{
    return mPolMan.GetVertexCount();
}

void Icosahedron::Update()
{
    mMVP = MatrixControl.PerspectiveView() * glm::mat4( 1.0f );
    mPolMan.Update();
}

void Icosahedron::Draw()
{
    mPolMan.Draw( mMVP );
}

glm::vec2 Icosahedron::UV( glm::vec3 pos )
{
    glm::vec2 uv;
    uv.x = 0.5f * ( 1.0f + std::atan2( pos.z , pos.x ) * ( Util::Maths::f1oPI ) );
    uv.y = std::acos( pos.y ) * ( Util::Maths::f1oPI );
    return uv;
}
