#include "Quad.hpp"

Quad::Quad( const glm::vec3 &pA, const glm::vec3 &pB, const glm::vec3 &pC, const glm::vec3 &pD )
{
    mA = pA;
    mB = pB;
    mC = pC;
    mD = pD;
    glm::vec3 dirA = glm::cross( pB - pA, pD - pA );
    mNormalA = glm::normalize( dirA );
    glm::vec3 dirB = glm::cross( pB - pD, pC - pD );
    mNormalB = glm::normalize( dirB );
}

Quad::~Quad()
{
    //dtor
}

glm::vec3 Quad::GetVerticeA() const
{
    return mA;
}

glm::vec3 Quad::GetVerticeB() const
{
    return mB;
}

glm::vec3 Quad::GetVerticeC() const
{
    return mC;
}

glm::vec3 Quad::GetVerticeD() const
{
    return mD;
}

glm::vec3 Quad::GetVertice( int i ) const
{
    switch( i ) {
        case 0:
            return mA;
        case 1:
            return mB;
        case 2:
            return mC;
        case 3:
            return mD;
    }
}

glm::vec3 Quad::GetNormalA() const
{
    return mNormalA;
}

glm::vec3 Quad::GetNormalB() const
{
    return mNormalB;
}