#include "RoundedCube.hpp"

#include <glm/gtx/compatibility.hpp>

#include "../Managers/MatrixManager.hpp"
#include "../Utilities.hpp"
#include "../RuntimeSettings.hpp"

RoundedCube::RoundedCube()
{
    //Set it to a static number, change size with a scale matrix
    float InitialSize = 1;

    Quad front(
                                           glm::vec3( -InitialSize,  InitialSize, InitialSize ),
                                           glm::vec3( -InitialSize, -InitialSize, InitialSize ),
                                           glm::vec3(  InitialSize, -InitialSize, InitialSize ),
                                           glm::vec3(  InitialSize,  InitialSize, InitialSize ) );

    Quad right(
                                           glm::vec3( InitialSize,  InitialSize, InitialSize ),
                                           glm::vec3( InitialSize, -InitialSize, InitialSize ),
                                           glm::vec3( InitialSize, -InitialSize,-InitialSize ),
                                           glm::vec3( InitialSize,  InitialSize,-InitialSize ) );

    Quad back(
                                          glm::vec3( InitialSize,  InitialSize, -InitialSize ),
                                          glm::vec3( InitialSize, -InitialSize, -InitialSize ),
                                          glm::vec3( -InitialSize, -InitialSize, -InitialSize ),
                                          glm::vec3( -InitialSize,  InitialSize, -InitialSize ) );

    Quad left(
                                          glm::vec3( -InitialSize,  InitialSize, -InitialSize ),
                                          glm::vec3( -InitialSize, -InitialSize, -InitialSize ),
                                          glm::vec3( -InitialSize, -InitialSize,  InitialSize ),
                                          glm::vec3( -InitialSize,  InitialSize,  InitialSize ) );

    Quad top(
                                         glm::vec3( -InitialSize,  InitialSize, -InitialSize ),
                                         glm::vec3( -InitialSize,  InitialSize,  InitialSize ),
                                         glm::vec3(  InitialSize,  InitialSize, InitialSize ),
                                         glm::vec3(  InitialSize,  InitialSize,  -InitialSize ) );

    Quad bottom(
                                            glm::vec3( -InitialSize, -InitialSize,  InitialSize ),
                                            glm::vec3( -InitialSize, -InitialSize, -InitialSize ),
                                            glm::vec3(  InitialSize, -InitialSize, -InitialSize ),
                                            glm::vec3(  InitialSize, -InitialSize,  InitialSize ) );

    mSideMan[Front] = new SideManager( front );
    mSideMan[Right] = new SideManager( right );
    mSideMan[Back] = new SideManager( back );
    mSideMan[Left] = new SideManager( left );
    mSideMan[Top] = new SideManager( top );
    mSideMan[Bottom] = new SideManager( bottom );

    mWaterSideMan[Front] = new WaterSideManager( front );
    mWaterSideMan[Right] = new WaterSideManager( right );
    mWaterSideMan[Back] = new WaterSideManager( back );
    mWaterSideMan[Left] = new WaterSideManager( left );
    mWaterSideMan[Top] = new WaterSideManager( top );
    mWaterSideMan[Bottom] = new WaterSideManager( bottom );

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
    mTexture = new Texture();

    for( int i = 0; i < 6; i++ ) {
        mSideMan[i]->SetNoise( mNoise );
    }

    RebuildSides();
}

RoundedCube::~RoundedCube()
{
    for( int i = 0; i < 6; i++ ) {
        delete mSideMan[i];
        delete mWaterSideMan[i];
    }

    delete mNoise;
    delete mTexture;
}

int RoundedCube::GetVertexCount()
{
    int count = 0;

    for( int i = 0; i < 6; i++ ) {
        count += mSideMan[i]->GetVertexCount();
        count += mWaterSideMan[i]->GetVertexCount();
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
        mWaterSideMan[i]->RebuildSide();
    }
}

void RoundedCube::Update( const Frustrum &frustrum )
{
    mMVP = MatrixControl.PerspectiveView() * glm::mat4( 1.0f );

    for( int i = 0; i < 6; i++ ) {
        mSideMan[i]->Update( frustrum );
        mWaterSideMan[i]->Update( frustrum );
    }
}

void RoundedCube::Draw( const Frustrum &frustrum )
{
    for( int i = 0; i < 6; i++ ) {
        mSideMan[i]->Draw( mMVP, frustrum );
        mWaterSideMan[i]->Draw( mMVP, frustrum );
    }
}

Texture *RoundedCube::GetTexture()
{
    return mTexture;
}

void RoundedCube::UpdateTextures()
{
    for( int i = 0; i < 6; i++ ) {
        mSideMan[i]->SetTexture( mTexture );
    }
}
