#include "RoundedCube.hpp"

#include <glm/gtx/compatibility.hpp>

#include "../MatrixManager.hpp"
#include "../Utilities.hpp"
#include "../RuntimeSettings.hpp"


RoundedCube::RoundedCube()
{
    //Set it to a static number, change size with a scale matrix
    float InitialSize = 1;
    mSideMan[Front] = new SideManager( Quad(
                                           glm::vec3( -InitialSize,  InitialSize, InitialSize ),
                                           glm::vec3( -InitialSize, -InitialSize, InitialSize ),
                                           glm::vec3(  InitialSize, -InitialSize, InitialSize ),
                                           glm::vec3(  InitialSize,  InitialSize, InitialSize ) ) );
    mSideMan[Right] = new SideManager( Quad(
                                           glm::vec3( InitialSize,  InitialSize, InitialSize ),
                                           glm::vec3( InitialSize, -InitialSize, InitialSize ),
                                           glm::vec3( InitialSize, -InitialSize,-InitialSize ),
                                           glm::vec3( InitialSize,  InitialSize,-InitialSize ) ) );
    mSideMan[Back] = new SideManager( Quad(
                                          glm::vec3( InitialSize,  InitialSize, -InitialSize ),
                                          glm::vec3( InitialSize, -InitialSize, -InitialSize ),
                                          glm::vec3( -InitialSize, -InitialSize, -InitialSize ),
                                          glm::vec3( -InitialSize,  InitialSize, -InitialSize ) ) );
    mSideMan[Left] = new SideManager( Quad(
                                          glm::vec3( -InitialSize,  InitialSize, -InitialSize ),
                                          glm::vec3( -InitialSize, -InitialSize, -InitialSize ),
                                          glm::vec3( -InitialSize, -InitialSize,  InitialSize ),
                                          glm::vec3( -InitialSize,  InitialSize,  InitialSize ) ) );
    mSideMan[Top] = new SideManager( Quad(
                                         glm::vec3( -InitialSize,  InitialSize, -InitialSize ),
                                         glm::vec3( -InitialSize,  InitialSize,  InitialSize ),
                                         glm::vec3(  InitialSize,  InitialSize, InitialSize ),
                                         glm::vec3(  InitialSize,  InitialSize,  -InitialSize ) ) );
    mSideMan[Bottom] = new SideManager( Quad(
                                            glm::vec3( -InitialSize, -InitialSize,  InitialSize ),
                                            glm::vec3( -InitialSize, -InitialSize, -InitialSize ),
                                            glm::vec3(  InitialSize, -InitialSize, -InitialSize ),
                                            glm::vec3(  InitialSize, -InitialSize,  InitialSize ) ) );
    RebuildSides();
}

RoundedCube::~RoundedCube()
{
    for( int i = 0; i < 6; i++ ) {
        delete mSideMan[i];
    }
}

int RoundedCube::GetVertexCount()
{
    int count = 0;

    for( int i = 0; i < 6; i++ ) {
        count += mSideMan[i]->GetVertexCount();
    }

    return count;
}

void RoundedCube::RebuildPlanes()
{
    //Only rebuild dynamically when realtime is wanted.
    if( !RuntimeSettings::Settings.RealtimeRebuild ) {
        return;
    }

    for( int i = 0; i < 6; i++ ) {
        mSideMan[i]->RebuildDistortions();
    }
}

void RoundedCube::RebuildSides()
{
    for( int i = 0; i < 6; i++ ) {
        mSideMan[i]->RebuildDistortions();
        mSideMan[i]->RebuildSide();
    }
}

void RoundedCube::Update( const Frustrum &frustrum )
{
    mMVP = MatrixControl.PerspectiveView() * glm::mat4( 1.0f );

    for( int i = 0; i < 6; i++ ) {
        mSideMan[i]->Update( frustrum );
    }
}

void RoundedCube::Draw()
{
    for( int i = 0; i < 6; i++ ) {
        mSideMan[i]->Draw( mMVP );
    }
}
