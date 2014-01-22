#ifndef FLATPLANE_HPP
#define FLATPLANE_HPP

#include "../../GLHelp/GLHelp.hpp"

class FlatPlane
{
public:
    FlatPlane( const glm::vec3 &center, const glm::vec2 &size, int spacing = 1 );
    virtual ~FlatPlane();

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

#endif //FLATPLANE_HPP
