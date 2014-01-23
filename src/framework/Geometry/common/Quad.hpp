#ifndef QUAD_HPP
#define QUAD_HPP

#include <glm/glm.hpp>

class Quad
{
public:
    Quad( const glm::vec3 &pA, const glm::vec3 &pB, const glm::vec3 &pC, const glm::vec3 &pD );
    ~Quad();
    glm::vec3 GetVerticeA() const;
    glm::vec3 GetVerticeB() const;
    glm::vec3 GetVerticeC() const;
    glm::vec3 GetVerticeD() const;
    glm::vec3 GetVertice( int i ) const;
    glm::vec3 GetNormalA() const;
    glm::vec3 GetNormalB() const;
protected:
    glm::vec3 mA, mB, mC, mD;

    glm::vec3 mNormalA, mNormalB;
private:
};

#endif // QUAD_HPP
