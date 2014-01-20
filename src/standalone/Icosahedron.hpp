#ifndef ICOSAHEDRON_HPP
#define ICOSAHEDRON_HPP

#include "framework/GLHelp/GLHelp.hpp"
#include "common/PolygonManager.hpp"

class Icosahedron
{
public:
    Icosahedron();
    ~Icosahedron();

    void Update();
    void Draw();
protected:
	PolygonManager mPolMan;
	glm::vec2 UV(glm::vec3 pos);

    glm::mat4 mMVP;
};
#endif //ICOSAHEDRON_HPP