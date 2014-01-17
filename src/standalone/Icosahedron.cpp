#include "./Icosahedron.hpp"

#include <glm/gtx/compatibility.hpp>

#include "framework/MatrixManager.hpp"
#include "framework/Utilities.hpp"

Icosahedron::Icosahedron()
{
	
    mTriangMan.AddTriangle(Triangle(
    	glm::vec3( -PLANETRADIUS,  PLANETRADIUS, PLANETRADIUS),
    	glm::vec3( -PLANETRADIUS, -PLANETRADIUS, PLANETRADIUS),
    	glm::vec3(  PLANETRADIUS,  PLANETRADIUS, PLANETRADIUS)));

    mTriangMan.AddTriangle(Triangle(
    	glm::vec3( PLANETRADIUS, PLANETRADIUS, PLANETRADIUS),
    	glm::vec3( -PLANETRADIUS, -PLANETRADIUS, PLANETRADIUS),
    	glm::vec3( PLANETRADIUS, -PLANETRADIUS, PLANETRADIUS)));

    mTriangMan.AddTriangle(Triangle(
    	glm::vec3( PLANETRADIUS,  PLANETRADIUS, PLANETRADIUS),
    	glm::vec3( PLANETRADIUS, -PLANETRADIUS, PLANETRADIUS),
    	glm::vec3( PLANETRADIUS,  PLANETRADIUS,-PLANETRADIUS)));

    mTriangMan.AddTriangle(Triangle(
    	glm::vec3( PLANETRADIUS,  PLANETRADIUS,-PLANETRADIUS),
    	glm::vec3( PLANETRADIUS, -PLANETRADIUS, PLANETRADIUS),
    	glm::vec3( PLANETRADIUS,  -PLANETRADIUS, -PLANETRADIUS)));

    mTriangMan.AddTriangle(Triangle(
    	glm::vec3(  PLANETRADIUS,  PLANETRADIUS, -PLANETRADIUS),
    	glm::vec3( PLANETRADIUS, -PLANETRADIUS, -PLANETRADIUS),
    	glm::vec3( -PLANETRADIUS,  PLANETRADIUS, -PLANETRADIUS)));

    mTriangMan.AddTriangle(Triangle(
    	glm::vec3( -PLANETRADIUS, PLANETRADIUS, -PLANETRADIUS),
    	glm::vec3( PLANETRADIUS, -PLANETRADIUS, -PLANETRADIUS),
    	glm::vec3( -PLANETRADIUS, -PLANETRADIUS, -PLANETRADIUS)));

    mTriangMan.AddTriangle(Triangle(
    	glm::vec3( -PLANETRADIUS,  PLANETRADIUS, -PLANETRADIUS),
    	glm::vec3( -PLANETRADIUS, -PLANETRADIUS, -PLANETRADIUS),
    	glm::vec3( -PLANETRADIUS,  PLANETRADIUS, PLANETRADIUS)));

    mTriangMan.AddTriangle(Triangle(
    	glm::vec3( -PLANETRADIUS,  PLANETRADIUS, PLANETRADIUS),
    	glm::vec3( -PLANETRADIUS, -PLANETRADIUS, -PLANETRADIUS),
    	glm::vec3( -PLANETRADIUS, -PLANETRADIUS, PLANETRADIUS)));

    mTriangMan.AddTriangle(Triangle(
    	glm::vec3( -PLANETRADIUS,  PLANETRADIUS, -PLANETRADIUS),
    	glm::vec3( -PLANETRADIUS,  PLANETRADIUS,  PLANETRADIUS),
    	glm::vec3(  PLANETRADIUS,  PLANETRADIUS,  -PLANETRADIUS)));

    mTriangMan.AddTriangle(Triangle(
    	glm::vec3(  PLANETRADIUS,  PLANETRADIUS, -PLANETRADIUS),
    	glm::vec3( -PLANETRADIUS,  PLANETRADIUS, PLANETRADIUS),
    	glm::vec3(  PLANETRADIUS,  PLANETRADIUS, PLANETRADIUS)));

    mTriangMan.AddTriangle(Triangle(
    	glm::vec3( -PLANETRADIUS, -PLANETRADIUS,  PLANETRADIUS),
    	glm::vec3( -PLANETRADIUS, -PLANETRADIUS, -PLANETRADIUS),
    	glm::vec3(  PLANETRADIUS, -PLANETRADIUS,  PLANETRADIUS)));

    mTriangMan.AddTriangle(Triangle(
    	glm::vec3(  PLANETRADIUS, -PLANETRADIUS, PLANETRADIUS),
    	glm::vec3( -PLANETRADIUS, -PLANETRADIUS, -PLANETRADIUS),
    	glm::vec3(  PLANETRADIUS, -PLANETRADIUS, -PLANETRADIUS)));


    for(int i = 0; i < 6; i++)
    {
        mTriangMan.Subdivide();
    }

    mTriangMan.BindData();
}

Icosahedron::~Icosahedron()
{
	
}

void Icosahedron::Update()
{
    mMVP = MatrixControl.PerspectiveView() * glm::mat4(1.0f);
}

void Icosahedron::Draw()
{
	mTriangMan.Draw(mMVP);
}

glm::vec2 Icosahedron::UV(glm::vec3 pos)
{
	glm::vec2 uv;
	uv.x = 0.5f * ( 1.0f + std::atan2( pos.z , pos.x ) * ( Util::Maths::f1oPI ));
	uv.y = std::acos( pos.y ) * ( Util::Maths::f1oPI );
	return uv;
}