#ifndef DEBUGLINES_HPP
#define DEBUGLINES_HPP

#include "../Includes.hpp"

#include "Shader.hpp"
#include "VBO.hpp"


class DebugLines
{
public:

    DebugLines();
    ~DebugLines();
    void SetCameraMatrix( glm::mat4 &pCameraMatrix );
    void SetPerspectiveMatrix( glm::mat4 &pPerspectiveMatrix );

    //Add a line to the drawer
    void AddLines ( const glm::vec3 &pVecA, const glm::vec3 &pVecB, const glm::vec3 &pColor );

    //Add a triangle, internally gets converted to 3 lines
    void AddTriangle ( const glm::vec3 &pVecA, const glm::vec3 &pVecB, const glm::vec3 &pVecC, const glm::vec3 &pColor );

    //Add a square, internally gets converted to 4 lines
    void AddQuad ( const glm::vec3 &pVecA, const glm::vec3 &pVecB, const glm::vec3 &pVecC, const glm::vec3 &pVecD, const glm::vec3 &pColor );

    void Draw();

protected:
private:
    std::vector<float> mPositionsList;
    std::vector<float> mColorsList;
    VBO mPositionBuffer;
    VBO mColorBuffer;
    int mVerticieAmount;
    Shader mLineShader;
    glm::mat4 *mCameraMatrix;
    glm::mat4 *mPerspectiveMatrix;
    glm::mat4 mMVP;
};

#endif // DEBUGLINES_HPP
