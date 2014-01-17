#ifndef PLANE_HPP
#define PLANE_HPP

#include "framework/GLHelp/GLHelp.hpp"

class Plane
{
public:
    Plane( const glm::vec3 &center, const glm::vec2 &size, int spacing = 1 );
    virtual ~Plane();

    virtual void Update();
    virtual void Draw( const glm::mat4 &MVP, const glm::mat4 &Model );
protected:
    VBO mVertexBuffer;
    std::vector<glm::vec3> mVertexList;

    VBO mNormalBuffer;
    std::vector<glm::vec2> mNormalList;

    VBO mIndexBuffer;
    std::vector<unsigned int> mIndexList;

    Texture *mTerrainTexture;
    Shader *mShader;
};

#endif //PLANE_HPP
