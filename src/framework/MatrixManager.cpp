#include "./MatrixManager.hpp"


MatrixManager::MatrixManager()
{
}


MatrixManager::~MatrixManager()
{
}

void MatrixManager::SetWidthHeight( int width, int height )
{
    mWidth = width;
    mHeight = height;
	mOrthogonal = glm::ortho<float>( 0.0f, (float)width, (float)height, 0.0f, mNearPlane, mFarPlane );
    mPerspective = glm::perspective( fieldOfView, width / ( float )height, mNearPlane, mFarPlane );
    mViewOrthographic = mOrthogonal * mView;
    mViewPerspective = mPerspective * mView;
}

void MatrixManager::SetPosition( const glm::vec3 &position )
{
    mPosition = position;
	mView = glm::lookAt( position, mLookAt, mUp );
    mViewOrthographic = mViewOrthographic * mView;
    mViewPerspective = mPerspective * mView;
}

void MatrixManager::SetLookAt( const glm::vec3 &lookAt )
{
    mLookAt = lookAt;
    mView = glm::lookAt( mPosition, lookAt, mUp );
    mViewOrthographic = mViewOrthographic * mView;
    mViewPerspective = mPerspective * mView;
}

void MatrixManager::SetUp( const glm::vec3 &up )
{
    mUp = up;
    mView = glm::lookAt( mPosition, mLookAt, up );
    mViewOrthographic = mViewOrthographic * mView;
    mViewPerspective = mPerspective * mView;
}