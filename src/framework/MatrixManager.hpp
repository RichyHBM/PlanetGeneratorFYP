#ifndef MATRIX_MANAGER_HPP
#define MATRIX_MANAGER_HPP

#include "./Includes.hpp"

class MatrixManager
{
    int mWidth, mHeight;
    float mNearPlane, mFarPlane;
    float fieldOfView;
    glm::vec3 mPosition, mLookAt, mUp;
    glm::mat4 mOrthogonal;
    glm::mat4 mPerspective;
    glm::mat4 mView;
    glm::mat4 mViewPerspective;
    glm::mat4 mViewOrthographic;

public:
    MatrixManager();
    ~MatrixManager();

    void SetWidthHeight( int width, int height );
    void SetPosition( const glm::vec3 &position );
    void SetLookAt( const glm::vec3 &lookAt );
    void SetUp( const glm::vec3 &up );

    const glm::mat4 &Orthographic() {
        return mOrthogonal;
    }
    const glm::mat4 &Perspective() {
        return mPerspective;
    }
    const glm::mat4 &View() {
        return mView;
    }
    const glm::mat4 &ViewPerspective() {
        return mViewPerspective;
    }
    const glm::mat4 &ViewOrthographic() {
        return mViewOrthographic;
    }
};

#endif //MATRIX_MANAGER_HPP