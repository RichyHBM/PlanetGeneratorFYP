#ifndef ROUNDEDCUBE_HPP
#define ROUNDEDCUBE_HPP

#include "../GLHelp/GLHelp.hpp"
#include "SideManager.hpp"
#include "../Physics/Frustrum.hpp"

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
    void Draw();

    void RebuildPlanes();
    void RebuildSides();

    int GetVertexCount();
protected:
    SideManager *mSideMan[6];
    glm::mat4 mMVP;
};
#endif //ROUNDEDCUBE_HPP