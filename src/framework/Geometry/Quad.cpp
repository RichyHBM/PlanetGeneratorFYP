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
    mSize = 1;
}

Quad::~Quad()
{
    //dtor
}

void Quad::SetSize(int size)
{
    mSize = size;
}

glm::vec3 Quad::GetVerticeA() const
{
    return glm::vec3( mA.x * mSize, mA.y * mSize, mA.z * mSize);
}

glm::vec3 Quad::GetVerticeB() const
{
    return glm::vec3( mB.x * mSize, mB.y * mSize, mB.z * mSize);
}

glm::vec3 Quad::GetVerticeC() const
{
    return glm::vec3( mC.x * mSize, mC.y * mSize, mC.z * mSize);
}

glm::vec3 Quad::GetVerticeD() const
{
    return glm::vec3( mD.x * mSize, mD.y * mSize, mD.z * mSize);
}

glm::vec3 Quad::GetVertice( int i ) const
{
    switch( i ) {
        case 0:
            return glm::vec3( mA.x * mSize, mA.y * mSize, mA.z * mSize);
        case 1:
            return glm::vec3( mB.x * mSize, mB.y * mSize, mB.z * mSize);
        case 2:
            return glm::vec3( mC.x * mSize, mC.y * mSize, mC.z * mSize);
        case 3:
            return glm::vec3( mD.x * mSize, mD.y * mSize, mD.z * mSize);
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