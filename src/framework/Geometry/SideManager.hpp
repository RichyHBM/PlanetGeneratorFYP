#ifndef SIDEMANAGER_HPP
#define SIDEMANAGER_HPP

#include "Quad.hpp"
#include <vector>
#include "../GLHelp/GLHelp.hpp"
#include "../RuntimeSettings.hpp"
#include "../Physics/Frustrum.hpp"
#include "../Noise/NoiseppNoise.hpp"

class SideManager
{
public:
    SideManager( const Quad &q );
    ~SideManager();
    std::vector<Quad> Subdivide( const Quad &q );
    void Draw( const glm::mat4 &MVP, const Frustrum &frustrum );
    void Update( const Frustrum &frustrum );
    void BindData();
    void Distort( );
    void Spherify();
    int GetVertexCount();
    void RebuildSide();
    void SetNoise( NoiseppNoise *noise );

protected:
    void NormalizeVert( glm::vec3 &v );

    Quad mInitialQuad;

    std::vector<Quad> mQuads;
    
    NoiseppNoise *mNoise;

    VBO mIndexBuffer;
    VBO mPositionBuffer;
    VBO mNormalBuffer;
    VBO mUVBuffer;
    Shader *mShader;
    Texture *mTerrainTexture;
private:
};

#endif // SIDEMANAGER_HPP
