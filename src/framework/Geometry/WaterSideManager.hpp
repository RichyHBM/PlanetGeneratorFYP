#ifndef WATERSIDEMANAGER_HPP
#define WATERSIDEMANAGER_HPP

#include "Quad.hpp"
#include <vector>
#include "../GLHelp/GLHelp.hpp"
#include "../RuntimeSettings.hpp"
#include "../Physics/Frustrum.hpp"
#include "../Noise/NoiseppNoise.hpp"

class WaterSideManager
{
public:
    WaterSideManager( const Quad &q );
    ~WaterSideManager();
    void Draw( const glm::mat4 &MVP, const Frustrum &frustrum );
    void Update( const Frustrum &frustrum );
    void BindData();
    void Spherify();
    int GetVertexCount();
    void RebuildSide();

protected:
    void NormalizeVert( glm::vec3 &v );

    Quad mInitialQuad;

    std::vector<Quad> mQuads;

    VBO mIndexBuffer;
    VBO mPositionBuffer;
    VBO mNormalBuffer;
    VBO mUVBuffer;
    Shader *mShader;
    Texture *mTerrainTexture;
private:
};

#endif // SIDEMANAGER_HPP
