#include "./MatrixManager.hpp"
#include "../Window/WindowSettings.hpp"

MatrixManager MatrixControl;

MatrixManager::MatrixManager()
{
}


MatrixManager::~MatrixManager()
{
}

void MatrixManager::Init()
{
    //Set all the variables
    mWidth = WindowSettings::Initial.GetWidth(), mHeight = WindowSettings::Initial.GetHeight();
    mNearPlane = 0.1f, mFarPlane = 2500.0f;
    mFieldOfView = 75.0f;
    mPosition = glm::vec3( 1,1,2 );
    mLookAt = glm::vec3( 0,0,0 );
    mUp = glm::vec3( 0,1,0 );
    //Screen aspect ratio
    mAspectRatio = mWidth / ( float )mHeight;
    //global orthographic matrix
    mOrthogonal = glm::ortho<float>( 0.0f, ( float )mWidth, ( float )mHeight, 0.0f, mNearPlane, mFarPlane );
    //global perspective matrix
    mPerspective = glm::perspective( mFieldOfView, mAspectRatio, mNearPlane, mFarPlane );
    //Cache a combination of all the matrix
    mView = glm::lookAt( mPosition, mLookAt, mUp );
    mOrthographicView = mOrthogonal * mView;
    mPerspectiveView = mPerspective * mView;
    mNearSize.y = 2 * glm::tan( Util::Maths::angToRad * mFieldOfView * 0.5 ) * mNearPlane;
    mNearSize.x = mNearSize.y * mAspectRatio;
    mFarSize.y = 2 * glm::tan( Util::Maths::angToRad * mFieldOfView * 0.5 ) * mFarPlane;
    mFarSize.x = mFarSize.y * mAspectRatio;
}

void MatrixManager::SetWidthHeight( int width, int height )
{
    mAspectRatio = mWidth / ( float )mHeight;
    mWidth = width;
    mHeight = height;
    mOrthogonal = glm::ortho<float>( 0.0f, ( float )width, ( float )height, 0.0f, mNearPlane, mFarPlane );
    mPerspective = glm::perspective( mFieldOfView, mAspectRatio, mNearPlane, mFarPlane );
    mOrthographicView = mOrthogonal * mView;
    mPerspectiveView = mPerspective * mView;
    mNearSize.y = 2 * glm::tan( Util::Maths::angToRad * mFieldOfView * 0.5 ) * mNearPlane;
    mNearSize.x = mNearSize.y * mAspectRatio;
    mFarSize.y = 2 * glm::tan( Util::Maths::angToRad * mFieldOfView * 0.5 ) * mFarPlane;
    mFarSize.x = mFarSize.y * mAspectRatio;
}

void MatrixManager::SetPosition( const glm::vec3 &position )
{
    mPosition = position;
    mView = glm::lookAt( mPosition, mLookAt, mUp );
    mOrthographicView = mOrthogonal * mView;
    mPerspectiveView = mPerspective * mView;
}

void MatrixManager::SetLookAt( const glm::vec3 &lookAt )
{
    mLookAt = lookAt;
    mView = glm::lookAt( mPosition, mLookAt, mUp );
    mOrthographicView = mOrthogonal * mView;
    mPerspectiveView = mPerspective * mView;
}

void MatrixManager::SetUp( const glm::vec3 &up )
{
    mUp = up;
    mView = glm::lookAt( mPosition, mLookAt, mUp );
    mOrthographicView = mOrthogonal * mView;
    mPerspectiveView = mPerspective * mView;
}