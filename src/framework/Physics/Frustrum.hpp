#ifndef FRUSTRUM_HPP
#define FRUSTRUM_HPP

#include "../Includes.hpp"
#include "Plane3d.hpp"
#include "../Geometry/Quad.hpp"
#include <vector>
#include "../GLHelp/GLHelp.hpp"

class Frustrum
{
public:
    Frustrum();
    ~Frustrum();

    bool InFrustrum( const glm::vec3 &point ) const;
    bool InFrustrumAndFacing( const Quad &quad ) const;

    void Update();
    void Draw();

    int Distances[10];

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