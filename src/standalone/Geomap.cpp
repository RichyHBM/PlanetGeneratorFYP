#include "Geomap.hpp"

#include "framework/Includes.hpp"
#include "framework/Utilities.hpp"
#include "framework/MatrixManager.hpp"

Geomap::Geomap()
{
    glm::mat4 Model = glm::mat4( 1.0f );
    mMVP = MatrixControl.PerspectiveView() * Model;
    int planes = 5;

    for( int y = -planes; y < planes+1; y++ ) {
        for( int x = -planes; x < planes+1; x++ ) {
            mPlanes.push_back( new Plane( glm::vec3( x * 50.0f, 0.0f, y * 50.0f ), glm::vec2( 50.0f ), 10 ) );
        }
    }
}

Geomap::~Geomap()
{
    for( int i = 0; i < mPlanes.size(); i++ ) {
        delete mPlanes[i];
        mPlanes[i] = NULL;
    }
}

void Geomap::Update()
{
    glm::mat4 Model( 1.0f );
    mMVP = MatrixControl.PerspectiveView() * Model;

    for( int i = 0; i < mPlanes.size(); i++ ) {
        mPlanes[i]->Update();
    }
}

void Geomap::Draw()
{
    for( int i = 0; i < mPlanes.size(); i++ ) {
        mPlanes[i]->Draw( mMVP );
    }
}
