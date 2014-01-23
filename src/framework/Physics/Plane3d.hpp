#ifndef PLANE3D_HPP
#define PLANE3D_HPP

#include "../Includes.hpp"

class Plane3d
{
public:
    Plane3d();
    Plane3d( const glm::vec3 &p1, const glm::vec3 &p2, const glm::vec3 &p3 );
    bool IntersectsWith( const Plane3d &plane );
    float GetDistance( const glm::vec3 &point );

    glm::vec3 Position();
    glm::vec3 Direction();

protected:
    glm::vec3 mPosition;
    glm::vec3 mDirection;
    float mDistance;
};

#endif //PLANE3D_HPP
