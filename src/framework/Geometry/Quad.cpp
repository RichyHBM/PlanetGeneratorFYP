#include "Quad.hpp"
#include "../Utilities.hpp"

Quad::Quad( const glm::vec3 &pA, const glm::vec3 &pB, const glm::vec3 &pC, const glm::vec3 &pD )
{
    mA = pA;
    mB = pB;
    mC = pC;
    mD = pD;
    glm::vec3 dirA = glm::cross( pB - pA, pD - pA );
    glm::vec3 dirB = glm::cross( pC - pB, pA - pB );
    glm::vec3 dirC = glm::cross( pD - pC, pB - pC );
    glm::vec3 dirD = glm::cross( pA - pD, pC - pD );
    mNormalA = glm::normalize( dirA );
    mNormalB = glm::normalize( dirB );
    mNormalC = glm::normalize( dirC );
    mNormalD = glm::normalize( dirD );
    mSize = 1;
}

Quad::~Quad()
{
    //dtor
}

std::vector<Quad> Quad::Subdivide( )
{
    //Split this quad into 4 quads
    std::vector<Quad> quads;
    glm::vec3 A = GetVerticeA(),
              B = GetVerticeB(),
              C = GetVerticeC(),
              D = GetVerticeD();
    glm::vec3 AB = ( A + B ) / glm::vec3( 2.0 );
    glm::vec3 BC = ( B + C ) / glm::vec3( 2.0 );
    glm::vec3 CD = ( C + D ) / glm::vec3( 2.0 );
    glm::vec3 DA = ( D + A ) / glm::vec3( 2.0 );
    glm::vec3 Middle = ( A + C ) / glm::vec3( 2.0 );
    quads.push_back( Quad( A, AB, Middle, DA ) );
    quads.push_back( Quad( AB, B, BC, Middle ) );
    quads.push_back( Quad( Middle, BC, C, CD ) );
    quads.push_back( Quad( DA, Middle, CD, D ) );
    return quads;
}

void Quad::SetSize( int size )
{
    mSize = size;
}

float Quad::ClosestDistance( const glm::vec3 &origin ) const
{
    //Closest corner of any of the quads corners to the origin
    float distA = glm::distance ( GetVerticeA(), origin );
    float distB = glm::distance ( GetVerticeB(), origin );
    float distC = glm::distance ( GetVerticeC(), origin );
    float distD = glm::distance ( GetVerticeD(), origin );
    return Util::MinValue( Util::MinValue( distA, distB ), Util::MinValue( distC, distD ) );
}

glm::vec3 Quad::GetVerticeA() const
{
    return glm::vec3( mA.x * mSize, mA.y * mSize, mA.z * mSize );
}

glm::vec3 Quad::GetVerticeB() const
{
    return glm::vec3( mB.x * mSize, mB.y * mSize, mB.z * mSize );
}

glm::vec3 Quad::GetVerticeC() const
{
    return glm::vec3( mC.x * mSize, mC.y * mSize, mC.z * mSize );
}

glm::vec3 Quad::GetVerticeD() const
{
    return glm::vec3( mD.x * mSize, mD.y * mSize, mD.z * mSize );
}

glm::vec3 Quad::GetVertice( int i ) const
{
    switch( i ) {
        case 0:
            return glm::vec3( mA.x * mSize, mA.y * mSize, mA.z * mSize );

        case 1:
            return glm::vec3( mB.x * mSize, mB.y * mSize, mB.z * mSize );

        case 2:
            return glm::vec3( mC.x * mSize, mC.y * mSize, mC.z * mSize );

        case 3:
            return glm::vec3( mD.x * mSize, mD.y * mSize, mD.z * mSize );
    }
}

glm::vec2 Quad::GetUVA() const
{
    return glm::vec2( 0,0 );
}

glm::vec2 Quad::GetUVB() const
{
    return glm::vec2( 0,1 );
}

glm::vec2 Quad::GetUVC() const
{
    return glm::vec2( 1,1 );
}

glm::vec2 Quad::GetUVD() const
{
    return glm::vec2( 1,0 );
}

glm::vec3 Quad::GetNormalA() const
{
    return mNormalA;
}

glm::vec3 Quad::GetNormalB() const
{
    return mNormalB;
}

glm::vec3 Quad::GetNormalC() const
{
    return mNormalC;
}

glm::vec3 Quad::GetNormalD() const
{
    return mNormalD;
}