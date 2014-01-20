#include "Quad.hpp"

Quad::Quad(const glm::vec3 &pA, const glm::vec3 &pB, const glm::vec3 &pC, const glm::vec3 &pD)
{
    mA = pA;
    mB = pB;
    mC = pC;
    mD = pD;
}

Quad::~Quad()
{
    //dtor
}

glm::vec3 &Quad::GetVerticeA()
{
    return mA;
}

glm::vec3 &Quad::GetVerticeB()
{
    return mB;
}

glm::vec3 &Quad::GetVerticeC()
{
    return mC;
}

glm::vec3 &Quad::GetVerticeD()
{
    return mD;
}
