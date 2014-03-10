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

    for( int i = 0; i < 6; i++ ) {
        mSideMan[i]->SetNoise( mNoise );
    }

    RebuildSides();
    mModel = glm::mat4( 1.0f );
}

RoundedCube::~RoundedCube()
{
    for( int i = 0; i < 6; i++ ) {
        delete mSideMan[i];
        delete mWaterSideMan[i];
    }

    delete mNoise;
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
    if( RuntimeSettings::Settings.SpinPlanet ) {
        double distance = glm::length( MatrixControl.Position() );
        distance -= RuntimeSettings::Settings.PlanetRadius * 2;
        distance *= 0.01f;
        std::abs( distance );
        float amount = ( float )( distance * RuntimeSettings::Settings.Delta );
        std::cout << amount << " : " << distance << std::endl;
        mModel = glm::rotate( mModel, amount, glm::vec3( 0.1f, 1.0f, 0.0f ) );
    }

    mMVP = MatrixControl.PerspectiveView() * mModel;

    for( int i = 0; i < 6; i++ ) {
        mSideMan[i]->Update( frustrum );
        mWaterSideMan[i]->Update( frustrum );
    }
}

void RoundedCube::Draw( const Frustrum &frustrum )
{
    for( int i = 0; i < 6; i++ ) {
        mSideMan[i]->Draw( mMVP, frustrum, mModel );
    }

    for( int i = 0; i < 6; i++ ) {
        mWaterSideMan[i]->Draw( mMVP, frustrum, mModel );
    }
}
