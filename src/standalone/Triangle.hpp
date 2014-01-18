#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include <glm/glm.hpp>

class Triangle
{
public:
    Triangle( glm::vec3 &pA, glm::vec3 &pB, glm::vec3 &pC );
    ~Triangle();
    glm::vec3 &GetVerticeA();
    glm::vec3 &GetVerticeB();
    glm::vec3 &GetVerticeC();
protected:
    glm::vec3 mA, mB, mC;
};

#endif // TRIANGLE_HPP
