#include "RoundedCube.hpp"

#include <glm/gtx/compatibility.hpp>

#include "../Managers/MatrixManager.hpp"
#include "../Utilities.hpp"
#include "../RuntimeSettings.hpp"

RoundedCube::RoundedCube()
{
    //Set it to a static number, change size with a scale matrix
    float InitialSize = 1;
    //Build the 6 sides
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
    //Set the sides
    mSideMan[Front] = new SideManager( front );
    mSideMan[Right] = new SideManager( right );
    mSideMan[Back] = new SideManager( back );
    mSideMan[Left] = new SideManager( left );
    mSideMan[Top] = new SideManager( top );
    mSideMan[Bottom] = new SideManager( bottom );
    //Do the same for the water sphere
    mWaterSideMan[Front] = new WaterSideManager( front );
    mWaterSideMan[Right] = new WaterSideManager( right );
    mWaterSideMan[Back] = new WaterSideManager( back );
    mWaterSideMan[Left] = new WaterSideManager( left );
    mWaterSideMan[Top] = new WaterSideManager( top );
    mWaterSideMan[Bottom] = new WaterSideManager( bottom );
    
    for( int i = 0; i < 6; i++ ) {
        mSideMan[i]->ResetNoise( );
    }

    //Do an initial build of the planet
    RebuildSides();
    mModel = glm::mat4( 1.0f );
}

RoundedCube::~RoundedCube()
{
    for( int i = 0; i < 6; i++ ) {
        delete mSideMan[i];
        delete mWaterSideMan[i];
    }
}

int RoundedCube::GetVertexCount()
{
    //Count all vertices in the spheres
    int count = 0;

    for( int i = 0; i < 6; i++ ) {
        count += mSideMan[i]->GetVertexCount();
        count += mWaterSideMan[i]->GetVertexCount();
    }

    return count;
}

void RoundedCube::RebuildNoise()
{
    for( int i = 0; i < 6; i++ ) {
        mSideMan[i]->ResetNoise( );
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
    //Spin plannet slower if user is closer to it
    if( RuntimeSettings::Settings.SpinPlanet ) {
        double distance = glm::length( MatrixControl.Position() );
        distance -= RuntimeSettings::Settings.PlanetRadius * 2;
        distance *= 0.01f;
        std::abs( distance );
        float amount = ( float )( distance * RuntimeSettings::Settings.Delta );
        mModel = glm::rotate( mModel, amount, glm::vec3( 0.1f, 1.0f, 0.0f ) );
    }

    mMVP = MatrixControl.PerspectiveView() * mModel;

    if( RuntimeSettings::Settings.RealtimeRebuild ) {

        sf::Thread *threads[12];

        for( int i = 0; i < 6; i++ ) {
            mSideMan[i]->SetFrustrum( frustrum );
            mWaterSideMan[i]->SetFrustrum( frustrum );

            threads[i] = new sf::Thread( &SideManager::Update, mSideMan[i] );
            threads[i + 6] = new sf::Thread( &WaterSideManager::Update, mWaterSideMan[i] );
        }

        for( int i = 0; i < 12; i++ ) {
            threads[i]->launch();
        }

        for( int i = 0; i < 12; i++ ) {
            threads[i]->wait();
            delete threads[i];
            threads[i] = NULL;
        }

        for( int i = 0; i < 6; i++ ) {
            mSideMan[i]->BindData();
            mWaterSideMan[i]->BindData();
        }
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
