#ifndef FRUSTRUM_HPP
#define FRUSTRUM_HPP

#include "../Includes.hpp"
#include "Plane3d.hpp"
#include "../Geometry/Quad.hpp"
#include <vector>
#include "../GLHelp/GLHelp.hpp"

#define DISTANCES_AMOUNT 6

class Frustrum
{
public:
    Frustrum();
    ~Frustrum();
    //Checks if a point is in the frustrum
    bool InFrustrum( const glm::vec3 &point ) const;
    //Checks if a quad is within thefrustrum and its front is towards the user
    bool InFrustrumAndFacing( const Quad &quad ) const;

    void Update();
    void Draw();
    //Distances for the LoD
    int Distances[DISTANCES_AMOUNT];

    glm::vec3 Position() const;

    enum PLANESIDE { Near, Far, Top, Bottom, Left, Right };
protected:
    Plane3d mPlanes[6];

    //Accronyms stand for: N/F near/far, T/B top/bottom, R/L right/left
    glm::vec3 mNTL, mNTR, mNBL, mNBR;
    glm::vec3 mFTL, mFTR, mFBL, mFBR;

    glm::vec3 mNearCenter, mFarCenter;

    glm::vec3 mPosition, mLookAt, mUp, X, Z;

    VBO mPositionBuffer;
    Shader *mShaderTransparent;
    Shader *mShader;
};

#endif //FRUSTRUM_HPP