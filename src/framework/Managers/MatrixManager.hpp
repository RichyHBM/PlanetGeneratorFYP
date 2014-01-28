#ifndef MATRIX_MANAGER_HPP
#define MATRIX_MANAGER_HPP

#include "../Includes.hpp"

class MatrixManager
{
    int mWidth, mHeight;
    float mNearPlane, mFarPlane;
    float mFieldOfView;
    float mAspectRatio;
    glm::vec2 mNearSize;
    glm::vec2 mFarSize;
    glm::vec3 mPosition, mLookAt, mUp;
    glm::mat4 mOrthogonal;
    glm::mat4 mPerspective;
    glm::mat4 mView;
    glm::mat4 mPerspectiveView;
    glm::mat4 mOrthographicView;

public:
    MatrixManager();
    ~MatrixManager();
    void Init();

    void SetWidthHeight( int width, int height );
    void SetPosition( const glm::vec3 &position );

    void SetLookAt( const glm::vec3 &lookAt );
    void SetUp( const glm::vec3 &up );

    const glm::vec2 NearPlaneSize() {
        return mNearSize;
    }
    const glm::vec2 FarPlaneSize() {
        return mFarSize;
    }
    float NearDistance() {
        return mNearPlane;
    }
    float FarDistance() {
        return mFarPlane;
    }
    float FoV() {
        return mFieldOfView;
    }
    float AspectRatio() {
        return mAspectRatio;
    }
    const glm::mat4 Orthographic() {
        return mOrthogonal;
    }
    const glm::mat4 Perspective() {
        return mPerspective;
    }
    const glm::mat4 View() {
        return mView;
    }
    const glm::mat4 PerspectiveView() {
        return mPerspectiveView;
    }
    const glm::mat4 OrthographicView() {
        return mOrthographicView;
    }

    const glm::vec3 Position() {
        return mPosition;
    }

    const glm::vec3 Up() {
        return mUp;
    }

    const glm::vec3 LookAt() {
        return mLookAt;
    }
};

extern MatrixManager MatrixControl;

#endif //MATRIX_MANAGER_HPP