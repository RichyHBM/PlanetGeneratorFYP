#include "Plane3d.hpp"

Plane3d::Plane3d()
{
    mDistance = 0;
}

Plane3d::Plane3d( const glm::vec3 &p1, const glm::vec3 &p2, const glm::vec3 &p3 )
{
    glm::vec3 v = p2- p1, u = p3-p1;
    mDirection = glm::normalize( glm::cross( v, u ) );
    mDistance = -( glm::dot( mDirection, p1 ) );
}


glm::vec3 Plane3d::Position()
{
    return mPosition;
}
glm::vec3 Plane3d::Direction()
{
    return mDirection;
}

float Plane3d::GetDistance( const glm::vec3 &point ) const
{
    return ( glm::dot( mDirection, point ) + mDistance );
}
