#include "./MatrixManager.hpp"
#include "./WindowSettings.hpp"

MatrixManager MatrixControl;

MatrixManager::MatrixManager()
{
}


MatrixManager::~MatrixManager()
{
}

void MatrixManager::Init()
{
    mWidth = WindowSettings::Initial.GetWidth(), mHeight = WindowSettings::Initial.GetHeight();
    mNearPlane = 0.1f, mFarPlane = 1000.0f;
    fieldOfView = 75.0f;
    //Use negative displacement to simulate left eye
    mDisplacement = 0.0f;
    mPosition = glm::vec3( 0,0,-2 );
    mLookAt = glm::vec3( 0,0,0 );
    mUp = glm::vec3( 0,1,0 );
    mOrthogonal = glm::ortho<float>( 0.0f, ( float )mWidth, ( float )mHeight, 0.0f, mNearPlane, mFarPlane );
    mPerspective = glm::perspective( fieldOfView, mWidth / ( float )mHeight, mNearPlane, mFarPlane );
    glm::vec3 left = glm::normalize( glm::cross( mLookAt - mPosition, mUp ) );
    mView = glm::lookAt( mPosition + ( left  * mDisplacement ), mLookAt, mUp );
    mOrthographicView = mOrthogonal * mView;
    mPerspectiveView = mPerspective * mView;
}

void MatrixManager::SetWidthHeight( int width, int height )
{
    mWidth = width;
    mHeight = height;
    mOrthogonal = glm::ortho<float>( 0.0f, ( float )width, ( float )height, 0.0f, mNearPlane, mFarPlane );
    mPerspective = glm::perspective( fieldOfView, width / ( float )height, mNearPlane, mFarPlane );
    mOrthographicView = mOrthogonal * mView;
    mPerspectiveView = mPerspective * mView;
}

void MatrixManager::SetPosition( const glm::vec3 &position )
{
    mPosition = position;
    glm::vec3 left = glm::normalize( glm::cross( mLookAt - mPosition, mUp ) );
    mView = glm::lookAt( mPosition + ( left  * mDisplacement ), mLookAt, mUp );
    mOrthographicView = mOrthogonal * mView;
    mPerspectiveView = mPerspective * mView;
}

void MatrixManager::SetDisplacement( float displacement )
{
    mDisplacement = displacement;
    glm::vec3 left = glm::cross( glm::normalize( mLookAt - mPosition ), mUp );
    mView = glm::lookAt( mPosition + ( left  * mDisplacement ), mLookAt, mUp );
    mOrthographicView = mOrthogonal * mView;
    mPerspectiveView = mPerspective * mView;
}

void MatrixManager::SetLookAt( const glm::vec3 &lookAt )
{
    mLookAt = lookAt;
    glm::vec3 left = glm::normalize( glm::cross( mLookAt - mPosition, mUp ) );
    mView = glm::lookAt( mPosition + ( left  * mDisplacement ), mLookAt, mUp );
    mOrthographicView = mOrthogonal * mView;
    mPerspectiveView = mPerspective * mView;
}

void MatrixManager::SetUp( const glm::vec3 &up )
{
    mUp = up;
    glm::vec3 left = glm::normalize( glm::cross( mLookAt - mPosition, mUp ) );
    mView = glm::lookAt( mPosition + ( left  * mDisplacement ), mLookAt, mUp );
    mOrthographicView = mOrthogonal * mView;
    mPerspectiveView = mPerspective * mView;
}