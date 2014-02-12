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
    void Draw( const glm::mat4 &MVP, const Frustrum &frustrum );
    void Update( const Frustrum &frustrum );
    void BindData();
    void Distort( );
    void Spherify();
    int GetVertexCount();
    void RebuildSide();
    void SetNoise( NoiseppNoise *noise );
    void SetTexture( Texture *texture );

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
    Texture *mSandTexture;
    Texture *mGrassTexture;
    Texture *mDirtTexture;
    Texture *mSnowTexture;
private:
};

#endif // SIDEMANAGER_HPP
