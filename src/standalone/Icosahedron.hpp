#ifndef ICOSAHEDRON_HPP
#define ICOSAHEDRON_HPP

#include "framework/GLHelp/GLHelp.hpp"
#include "common/TriangleManager.hpp"

class Icosahedron
{
public:
    Icosahedron();
    ~Icosahedron();

    void Update();
    void Draw();
protected:
	TriangleManager mTriangMan;
	glm::vec2 UV(glm::vec3 pos);

    glm::mat4 mMVP;
};
#endif //ICOSAHEDRON_HPP