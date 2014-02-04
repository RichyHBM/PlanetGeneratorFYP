#ifndef ROUNDEDCUBE_HPP
#define ROUNDEDCUBE_HPP

#include "../GLHelp/GLHelp.hpp"
#include "SideManager.hpp"
#include "../Physics/Frustrum.hpp"
#include "../Noise/NoiseppNoise.hpp"

class RoundedCube
{
public:
    enum Side {
        Top,
        Bottom,
        Left,
        Right,
        Front,
        Back
    };
    RoundedCube();
    ~RoundedCube();

    void Update( const Frustrum &frustrum );
    void Draw( const Frustrum &frustrum );

    void RebuildSides();
    void RebuildNoise();

    int GetVertexCount();
    Texture *GetTexture();
    void UpdateTextures();
protected:
    NoiseppNoise *mNoise;
    SideManager *mSideMan[6];
    glm::mat4 mMVP;
    Texture *mTexture;
};
#endif //ROUNDEDCUBE_HPP