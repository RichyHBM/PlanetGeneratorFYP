#ifndef QUAD_HPP
#define QUAD_HPP

#include <glm/glm.hpp>

class Quad
{
public:
    Quad( const glm::vec3 &pA, const glm::vec3 &pB, const glm::vec3 &pC, const glm::vec3 &pD );
    ~Quad();
    glm::vec3 &GetVerticeA();
    glm::vec3 &GetVerticeB();
    glm::vec3 &GetVerticeC();
    glm::vec3 &GetVerticeD();
    glm::vec3 &GetVertice( int i );
protected:
    glm::vec3 mA, mB, mC, mD;
private:
};

#endif // QUAD_HPP
