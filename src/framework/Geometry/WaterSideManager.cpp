#include <glm/gtx/transform2.hpp>

#include "WaterSideManager.hpp"

#include "../Managers/ResourceManager.hpp"
#include "../Managers/MatrixManager.hpp"
#include "../Noise/NoiseppNoise.hpp"

WaterSideManager::WaterSideManager( const Quad &q ): mInitialQuad( q )
{
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
    mSinDisplacement += RuntimeSettings::Settings.SinAmount;

    if( !RuntimeSettings::Settings.RealtimeRebuild ) {
        return;
    }

    mQuads.clear();
    mInitialQuad.SetSize( RuntimeSettings::Settings.WaterRadius );
    mQuads.push_back( mInitialQuad );

    //First subdivide to level 4, regardless of distance
    for( int subd = 0; subd < 4; subd++ ) {
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

    Spherify();
    std::vector<Quad> mTempQuads;

    //Next subdivide quads that are within the distance required
    for( int i = 0; i < mQuads.size(); i++ ) {
        float distance = mQuads[i].ClosestDistance( frustrum.Position() );
        int subdivisionlevel = 0;

        if( distance < 0 ) {
            std::cout << Util::Vec3ToString( frustrum.Position() ) << " " << Util::Vec3ToString( mQuads[i].GetVerticeA() ) << " " << distance << std::endl;
        }

        if( distance < frustrum.DistNear1 ) {
            subdivisionlevel = 5;

        } else if( distance < frustrum.DistNear2 ) {
            subdivisionlevel = 4;

        } else if( distance < frustrum.DistMedium3 ) {
            subdivisionlevel = 3;

        } else if( distance < frustrum.DistFar4 ) {
            subdivisionlevel = 2;

        } else if( distance < frustrum.DistFar5 ) {
            subdivisionlevel = 1;
        }

        std::vector<Quad> tempQuads;
        tempQuads.push_back( mQuads[i] );

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
    Spherify();
    BindData();
}

void WaterSideManager::RebuildSide()
{
    mQuads.clear();
    mInitialQuad.SetSize( RuntimeSettings::Settings.WaterRadius );
    mQuads.push_back( mInitialQuad );

    for( int subd = 0; subd < RuntimeSettings::Settings.Subdivisions; subd++ ) {
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

    Spherify();
    BindData();
}

void WaterSideManager::Draw( const glm::mat4 &MVP, const Frustrum &frustrum )
{
    //If the initial quad isnt in the frustrum then skip the draw
    if( !RuntimeSettings::Settings.DrawHidden )
        if( !frustrum.InFrustrumAndFacing( mInitialQuad ) ) {
            return;
        }

    glm::mat4 NormalMat = glm::transpose( glm::inverse( glm::mat4( 1.0f ) ) );
    glm::mat4 MV = MatrixControl.View();

    mShader->Bind();
    glUniformMatrix4fv( mShader->GetUniform( "MVP" ), 1, GL_FALSE, &MVP[0][0] );
    glUniformMatrix4fv( mShader->GetUniform( "MV" ), 1, GL_FALSE, &MV[0][0] );
    glUniformMatrix4fv( mShader->GetUniform( "NormalMat" ), 1, GL_FALSE, &NormalMat[0][0] );
    glUniform3fv( mShader->GetUniform( "LightDirection" ), 1, &RuntimeSettings::Settings.LightDirection[0] );

    glm::vec3 lookDirection(MatrixControl.LookAt() - MatrixControl.Position());

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
