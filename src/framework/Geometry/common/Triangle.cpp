#include "Triangle.hpp"

Triangle::Triangle( const glm::vec3 &pA, const glm::vec3 &pB, const glm::vec3 &pC )
{
    mA = pA;
    mB = pB;
    mC = pC;
}

Triangle::~Triangle()
{
    //dtor
}

glm::vec3 &Triangle::GetVerticeA()
{
    return mA;
}

glm::vec3 &Triangle::GetVerticeB()
{
    return mB;
}

glm::vec3 &Triangle::GetVerticeC()
{
    return mC;
}

