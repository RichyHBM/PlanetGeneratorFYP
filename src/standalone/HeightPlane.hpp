#ifndef HEIGHT_PLANE_HPP
#define HEIGHT_PLANE_HPP

#include "framework/GLHelp/GLHelp.hpp"

class HeightPlane
{
public:
    HeightPlane( const glm::vec3 &center, const glm::vec2 &size, int spacing = 1 );
    virtual ~HeightPlane();

    void Update();
    void Draw( const glm::mat4 &MVP );
protected:
    VBO mHeightBuffer;
    std::vector<float> mHeightList;

    VBO mVertexBuffer;
    std::vector<glm::vec3> mVertexList;

    VBO mTexCoordBuffer;
    std::vector<glm::vec2> mTexCoordList;

    VBO mIndexBuffer;
    std::vector<unsigned int> mIndexList;

    Texture *mTerrainTexture;
    Shader *mShader;
};

#endif //HEIGHT_PLANE_HPP
