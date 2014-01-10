#include "Geomap.hpp"

#include "framework/Includes.hpp"
#include "framework/Utilities.hpp"
#include "framework/MatrixManager.hpp"

Geomap::Geomap()
{
    glm::mat4 Model = glm::mat4( 1.0f );
    mMVP = MatrixControl.PerspectiveView() * Model;
    
    // Need to build a grid, middle will have small distance and exterior rings will have bigger distance
    
    int hPlanes = 8;
    int size = 50;
    int hSize = size/2;

    for( int y = -hPlanes; y < hPlanes; y++ ) {
        for( int x = -hPlanes; x < hPlanes; x++ ) {

            int spacing = 1;

            if( y > 3 || y < -4 || x > 3 || x < -4 )
                spacing = 10;
            else if( y > 1 || y < -2 || x > 1 || x < -2 )
                spacing = 5;
            else if( y > 0 || y < -1 || x > 0 || x < -1 )
                spacing = 2;

            mPlanes.push_back( 
                new Plane( 
                    glm::vec3( (x * size) + hSize, 0.0f, (y * size) + hSize ), 
                    glm::vec2( size ), 
                    spacing ) 
                );
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
    glm::vec3 pos = MatrixControl.Position();
    pos.y = 0;
    mModel = glm::mat4( glm::translate( pos ) );
    mMVP = MatrixControl.PerspectiveView() * mModel;

    for( int i = 0; i < mPlanes.size(); i++ ) {
        mPlanes[i]->Update();
    }
}

void Geomap::Draw()
{
    for( int i = 0; i < mPlanes.size(); i++ ) {
        mPlanes[i]->Draw( mMVP, mModel );
    }
}
