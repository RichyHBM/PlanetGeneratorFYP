#ifndef ICOSAHEDRON_HPP
#define ICOSAHEDRON_HPP

#include "../GLHelp/GLHelp.hpp"
#include "common/PolygonManager.hpp"

class Icosahedron
{
public:
    Icosahedron();
    ~Icosahedron();

    void Update();
    void Draw();

    int GetVertexCount();
protected:
    PolygonManager mPolMan;
    glm::vec2 UV( glm::vec3 pos );

    glm::mat4 mMVP;
};
#endif //ICOSAHEDRON_HPP