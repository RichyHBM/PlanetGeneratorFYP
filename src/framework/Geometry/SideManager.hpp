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
    void Draw( const glm::mat4 &MVP, const Frustrum &frustrum, const glm::mat4 &Model );
    void Update( );
    void SetFrustrum( const Frustrum &frustrum );
    //Binds updated data to the gpu
    void BindData();
    //Add noise
    void Distort( );
    //Make cube into sphere
    void Spherify();
    int GetVertexCount();
    void RebuildSide();
    void ResetNoise( );

protected:
    void NormalizeVert( glm::vec3 &v );

    Quad mInitialQuad;

    std::vector<Quad> mQuads;

    std::vector<Quad> mRealtimeQuads;

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
    const Frustrum *mFrustrum;
private:
};

#endif // SIDEMANAGER_HPP
