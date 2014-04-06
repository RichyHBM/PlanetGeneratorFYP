#ifndef PLANE3D_HPP
#define PLANE3D_HPP

#include "../Includes.hpp"

class Plane3d
{
public:
    Plane3d();
    //can generate a plane using just 3 points that are within the plane
    Plane3d( const glm::vec3 &p1, const glm::vec3 &p2, const glm::vec3 &p3 );
    //Checks for intersection between a plane and this plane
    bool IntersectsWith( const Plane3d &plane );
    //Gets the distance to an object, with positive being infront and negative being behind
    float GetDistance( const glm::vec3 &point ) const;

    glm::vec3 Position();
    glm::vec3 Direction();

protected:
    glm::vec3 mPosition;
    glm::vec3 mDirection;
    float mDistance;
};

#endif //PLANE3D_HPP
