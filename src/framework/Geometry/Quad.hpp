#ifndef QUAD_HPP
#define QUAD_HPP

#include <glm/glm.hpp>
#include <vector>

class Quad
{
public:
    Quad( const glm::vec3 &pA, const glm::vec3 &pB, const glm::vec3 &pC, const glm::vec3 &pD );
    ~Quad();
    std::vector<Quad> Subdivide( );
    glm::vec3 GetVerticeA() const;
    glm::vec3 GetVerticeB() const;
    glm::vec3 GetVerticeC() const;
    glm::vec3 GetVerticeD() const;
    glm::vec3 GetVertice( int i ) const;
    glm::vec3 GetNormalA() const;
    glm::vec3 GetNormalB() const;
    glm::vec3 GetNormalC() const;
    glm::vec3 GetNormalD() const;

    glm::vec2 GetUVA() const;
    glm::vec2 GetUVB() const;
    glm::vec2 GetUVC() const;
    glm::vec2 GetUVD() const;

    float ClosestDistance( const glm::vec3 &origin ) const;

    void SetSize( int size );
protected:
    glm::vec3 mA, mB, mC, mD;
    int mSize;
    glm::vec3 mNormalA, mNormalB, mNormalC, mNormalD;
private:
};

#endif // QUAD_HPP
