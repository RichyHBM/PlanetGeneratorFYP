#include <glm/gtx/transform2.hpp>

#include "WaterSideManager.hpp"

#include "../Managers/ResourceManager.hpp"
#include "../Managers/MatrixManager.hpp"
#include "../Noise/NoiseppNoise.hpp"

WaterSideManager::WaterSideManager( const Quad &q ): mInitialQuad( q )
{
    //Load all resources
    mShader = ResourceManager::GetShader( "Water", "./Resources/Water.vert" ,"./Resources/Water.frag" );
    mPositionBuffer.SetAttributeIndex( mShader->GetAttribute( "Position" ) );
    mNormalBuffer.SetAttributeIndex( mShader->GetAttribute( "Normal" ) );
    mQuads.push_back( mInitialQuad );
    mSinDisplacement = 0;
}

WaterSideManager::~WaterSideManager()
{
    mShader = NULL;
}

void WaterSideManager::NormalizeVert( glm::vec3 &v )
{
    //Normalise the vector length to a given length
    float length = RuntimeSettings::Settings.WaterRadius * 2;
    float dist = glm::length( v );
    v.x = v.x * length / dist;
    v.y = v.y * length / dist;
    v.z = v.z * length / dist;
}

int WaterSideManager::GetVertexCount()
{
    return mQuads.size() * 2;
}

void WaterSideManager::Spherify()
{
    //Pass all vertices through the normalisation function
    for( int i = 0; i < mQuads.size(); i++ ) {
        glm::vec3 A = mQuads[i].GetVerticeA(),
                  B = mQuads[i].GetVerticeB(),
                  C = mQuads[i].GetVerticeC(),
                  D = mQuads[i].GetVerticeD();
        NormalizeVert( A );
        NormalizeVert( B );
        NormalizeVert( C );
        NormalizeVert( D );
        mQuads[i] = Quad( A, B, C, D );
    }
}

void WaterSideManager::BindData()
{
    //Binds data to the vbo's
    std::vector<glm::vec3> mPositionsList;
    std::vector<glm::vec3> mNormalsList;
    std::vector<glm::vec2> mUVsList;
    std::vector<unsigned int> mIndices;

    for( int i = 0; i < mQuads.size(); i++ ) {
        mPositionsList.push_back( mQuads[i].GetVerticeA() );
        mPositionsList.push_back( mQuads[i].GetVerticeB() );
        mPositionsList.push_back( mQuads[i].GetVerticeC() );
        mPositionsList.push_back( mQuads[i].GetVerticeD() );
        mNormalsList.push_back( mQuads[i].GetNormalA() );
        mNormalsList.push_back( mQuads[i].GetNormalB() );
        mNormalsList.push_back( mQuads[i].GetNormalC() );
        mNormalsList.push_back( mQuads[i].GetNormalD() );
        int size = mPositionsList.size();
        mIndices.push_back( size - 4 );
        mIndices.push_back( size - 3 );
        mIndices.push_back( size - 1 );
        mIndices.push_back( size - 1 );
        mIndices.push_back( size - 3 );
        mIndices.push_back( size - 2 );
    }

    mPositionBuffer.AddVectorData( mPositionsList, sizeof( glm::vec3 ) );
    mPositionBuffer.SetAttributeIndex( mShader->GetAttribute( "Position" ) );
    mNormalBuffer.AddVectorData( mNormalsList, sizeof( glm::vec3 ) );
    mNormalBuffer.SetAttributeIndex( mShader->GetAttribute( "Normal" ) );
    mIndexBuffer.AddVectorData( mIndices, sizeof( unsigned int ) );
    mIndexBuffer.SetTarget( GL_ELEMENT_ARRAY_BUFFER );
}


void WaterSideManager::Update( const Frustrum &frustrum )
{
    //Move waves
    mSinDisplacement += RuntimeSettings::Settings.SinAmount;

    //Only do this if in realtime
    if( !RuntimeSettings::Settings.RealtimeRebuild ) {
        return;
    }

    mQuads.clear();
    mQuads = mRealtimeQuads;
    std::vector<Quad> mTempQuads;

    //Next subdivide quads that are within the distance required
    for( int i = 0; i < mQuads.size(); i++ ) {
        //Only do for quads in view
        if( !frustrum.InFrustrumAndFacing( mQuads[i] ) ) {
            if( RuntimeSettings::Settings.DrawHidden ) {
                mTempQuads.push_back( mQuads[i] );
            }

            continue;
        }

        //Get the distance of the current quad
        float distance = mQuads[i].ClosestDistance( frustrum.Position() );
        int subdivisionlevel = 0;

        //Check to what level of subdivision to go to
        for( int d = 0; d < DISTANCES_AMOUNT - 3; d++ ) {
            if( distance < frustrum.Distances[d] ) {
                subdivisionlevel = d;
            }
        }

        std::vector<Quad> tempQuads;
        tempQuads.push_back( mQuads[i] );

        //Subdivide quads to that level
        for( int j = 0; j < subdivisionlevel; j++ ) {
            std::vector<Quad> subdividedQuads;

            for( int h = 0; h < tempQuads.size(); h++ ) {
                std::vector<Quad> subQuads = tempQuads[h].Subdivide();
                subdividedQuads.push_back( subQuads[0] );
                subdividedQuads.push_back( subQuads[1] );
                subdividedQuads.push_back( subQuads[2] );
                subdividedQuads.push_back( subQuads[3] );
            }

            tempQuads = subdividedQuads;
        }

        for( int j = 0; j < tempQuads.size(); j++ ) {
            mTempQuads.push_back( tempQuads[j] );
        }
    }

    mQuads = mTempQuads;
    BindData();
}

void WaterSideManager::RebuildSide()
{
    mRealtimeQuads.clear();
    mInitialQuad.SetSize( RuntimeSettings::Settings.WaterRadius );
    mRealtimeQuads.push_back( mInitialQuad );

    //Build up the cached sphere to level 6
    for( int subd = 0; subd < 6; subd++ ) {
        std::vector<Quad> mTempQuads;

        for( int i = 0; i < mRealtimeQuads.size(); i++ ) {
            std::vector<Quad> subQuads = mRealtimeQuads[i].Subdivide();
            mTempQuads.push_back( subQuads[0] );
            mTempQuads.push_back( subQuads[1] );
            mTempQuads.push_back( subQuads[2] );
            mTempQuads.push_back( subQuads[3] );
        }

        mRealtimeQuads = mTempQuads;
    }

    //Make the current sphere use the cache
    mQuads = mRealtimeQuads;
    //Keep subdividing if neccesairy

    for( int subd = 6; subd < RuntimeSettings::Settings.Subdivisions; subd++ ) {
        std::vector<Quad> mTempQuads;

        for( int i = 0; i < mQuads.size(); i++ ) {
            std::vector<Quad> subQuads = mQuads[i].Subdivide();
            mTempQuads.push_back( subQuads[0] );
            mTempQuads.push_back( subQuads[1] );
            mTempQuads.push_back( subQuads[2] );
            mTempQuads.push_back( subQuads[3] );
        }

        mQuads = mTempQuads;
    }

    //Spherify the cached quads
    for( int i = 0; i < mRealtimeQuads.size(); i++ ) {
        glm::vec3 A = mRealtimeQuads[i].GetVerticeA(),
                  B = mRealtimeQuads[i].GetVerticeB(),
                  C = mRealtimeQuads[i].GetVerticeC(),
                  D = mRealtimeQuads[i].GetVerticeD();
        NormalizeVert( A );
        NormalizeVert( B );
        NormalizeVert( C );
        NormalizeVert( D );
        mRealtimeQuads[i] = Quad( A, B, C, D );
    }

    Spherify();
    BindData();
}

void WaterSideManager::Draw( const glm::mat4 &MVP, const Frustrum &frustrum, const glm::mat4 &Model )
{
    glm::mat4 NormalMat = glm::transpose( glm::inverse( Model ) );
    glm::mat4 MV = MatrixControl.View();
    mShader->Bind();
    glUniformMatrix4fv( mShader->GetUniform( "MVP" ), 1, GL_FALSE, &MVP[0][0] );
    glUniformMatrix4fv( mShader->GetUniform( "MV" ), 1, GL_FALSE, &MV[0][0] );
    glUniformMatrix4fv( mShader->GetUniform( "NormalMat" ), 1, GL_FALSE, &NormalMat[0][0] );
    glUniform3fv( mShader->GetUniform( "LightDirection" ), 1, &RuntimeSettings::Settings.LightDirection[0] );
    glm::vec3 lookDirection( MatrixControl.LookAt() - MatrixControl.Position() );
    glUniform3fv( mShader->GetUniform( "LookDirection" ), 1, &lookDirection[0] );
    glUniform4fv( mShader->GetUniform( "WaterColor" ), 1, &RuntimeSettings::Settings.WaterColor[0] );
    glUniform1f( mShader->GetUniform( "SinNumber" ), mSinDisplacement );
    glUniform1f( mShader->GetUniform( "WaveSize" ), RuntimeSettings::Settings.WaveSize );
    mPositionBuffer.Bind( 3 );
    mNormalBuffer.Bind( 3 );
    mIndexBuffer.Bind();
    glDrawElements( GL_TRIANGLES, mQuads.size() * 6, GL_UNSIGNED_INT, ( void * )0 );
    mIndexBuffer.Unbind();
    mNormalBuffer.Unbind();
    mPositionBuffer.Unbind();
    Texture::Unbind();
    Shader::Unbind();
}
