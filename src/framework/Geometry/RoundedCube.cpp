#include "RoundedCube.hpp"

#include <glm/gtx/compatibility.hpp>

#include "../Managers/MatrixManager.hpp"
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
    mNoise = new NoiseppNoise(
        RuntimeSettings::Settings.Seed,
        RuntimeSettings::Settings.Octaves,
        RuntimeSettings::Settings.Persistence,
        RuntimeSettings::Settings.Frequency,
        RuntimeSettings::Settings.Quality,
        RuntimeSettings::Settings.Scale,
        RuntimeSettings::Settings.Lacunarity,
        RuntimeSettings::Settings.Distortion
    );

    for( int i = 0; i < 6; i++ ) {
        mSideMan[i]->SetNoise( mNoise );
    }

    RebuildSides();
}

RoundedCube::~RoundedCube()
{
    for( int i = 0; i < 6; i++ ) {
        delete mSideMan[i];
    }

    delete mNoise;
}

int RoundedCube::GetVertexCount()
{
    int count = 0;

    for( int i = 0; i < 6; i++ ) {
        count += mSideMan[i]->GetVertexCount();
    }

    return count;
}

void RoundedCube::RebuildNoise()
{
    delete mNoise;
    mNoise = NULL;
    mNoise = new NoiseppNoise(
        RuntimeSettings::Settings.Seed,
        RuntimeSettings::Settings.Octaves,
        RuntimeSettings::Settings.Persistence,
        RuntimeSettings::Settings.Frequency,
        RuntimeSettings::Settings.Quality,
        RuntimeSettings::Settings.Scale,
        RuntimeSettings::Settings.Lacunarity,
        RuntimeSettings::Settings.Distortion
    );

    for( int i = 0; i < 6; i++ ) {
        mSideMan[i]->SetNoise( mNoise );
    }
}

void RoundedCube::RebuildSides()
{
    for( int i = 0; i < 6; i++ ) {
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

void RoundedCube::Draw( const Frustrum &frustrum )
{
    for( int i = 0; i < 6; i++ ) {
        mSideMan[i]->Draw( mMVP, frustrum );
    }
}
