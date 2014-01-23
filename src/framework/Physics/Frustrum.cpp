#include "Frustrum.hpp"

#include "../MatrixManager.hpp"
#include "../ResourceManager.hpp"
#include "../Utilities.hpp"

Frustrum::Frustrum()
{
    mShaderTransparent = ResourceManager::GetShader( "SimpleTransparent", "./Resources/Simple.vert" ,"./Resources/SimpleTransparent.frag" );
    mShader = ResourceManager::GetShader( "Simple", "./Resources/Simple.vert" ,"./Resources/Simple.frag" );
    mPosition = MatrixControl.Position();
    mLookAt  = MatrixControl.LookAt();
    Z = glm::normalize( mPosition - mLookAt );
    X = glm::normalize( glm::cross( MatrixControl.Up(), Z ) );
    mUp = glm::cross( Z, X );
    mFTL = mFarCenter + ( mUp * MatrixControl.FarPlaneSize().y/2.0f ) - ( X * MatrixControl.FarPlaneSize().x/2.0f );
    mFTR = mFarCenter + ( mUp * MatrixControl.FarPlaneSize().y/2.0f ) + ( X * MatrixControl.FarPlaneSize().x/2.0f );
    mFBL = mFarCenter - ( mUp * MatrixControl.FarPlaneSize().y/2.0f ) - ( X * MatrixControl.FarPlaneSize().x/2.0f );
    mFBR = mFarCenter - ( mUp * MatrixControl.FarPlaneSize().y/2.0f ) + ( X * MatrixControl.FarPlaneSize().x/2.0f );
    mNTL = mNearCenter + ( mUp * MatrixControl.NearPlaneSize().y / 2.0f ) - ( X * MatrixControl.NearPlaneSize().x/2.0f );
    mNTR = mNearCenter + ( mUp * MatrixControl.NearPlaneSize().y / 2.0f ) + ( X * MatrixControl.NearPlaneSize().x/2.0f );
    mNBL = mNearCenter - ( mUp * MatrixControl.NearPlaneSize().y / 2.0f ) - ( X * MatrixControl.NearPlaneSize().x/2.0f );
    mNBR = mNearCenter - ( mUp * MatrixControl.NearPlaneSize().y / 2.0f ) + ( X * MatrixControl.NearPlaneSize().x/2.0f );
    mPlanes[TOP] = Plane3d( mNTR, mNTL, mFTL );
    mPlanes[BOTTOM] = Plane3d( mNBL, mNBR, mFBR );
    mPlanes[LEFT] = Plane3d( mNTL, mNBL, mFBL );
    mPlanes[RIGHT] = Plane3d( mNBR, mNTR, mFBR );
    mPlanes[NEAR] = Plane3d( mNTL, mNTR, mNBR );
    mPlanes[FAR] = Plane3d( mFTR, mFTL, mFBL );
}

Frustrum::~Frustrum()
{
    mShader = NULL;
}

bool Frustrum::InFrustrum( const glm::vec3 &point )
{
    for( int i = 0; i < 6; i++ ) {
        if ( mPlanes[i].GetDistance( point ) < 0.0f ) {
            return false;
        }
    }

    return true;
}

bool Frustrum::InFrustrumAndFacing( Quad &quad )
{
    bool inFrustrum = false;

    for( int i = 0; i < 4; i++ ) {
        if ( InFrustrum( quad.GetVertice( i ) ) ) {
            inFrustrum = true;
        }
    }

    if( !inFrustrum ) {
        return false;
    }

    //Check direction of camera dot quad normal is negative
    return true;
}

void Frustrum::Update()
{
    mPosition = MatrixControl.Position();
    mLookAt  = MatrixControl.LookAt();
    Z = glm::normalize( mPosition - mLookAt );
    X = glm::normalize( glm::cross( MatrixControl.Up(), Z ) );
    mUp = glm::cross( Z, X );
    mNearCenter = mPosition + ( -Z * MatrixControl.NearDistance() );
    mFarCenter = mPosition + ( -Z * MatrixControl.FarDistance() );
    mFTL = mFarCenter + ( mUp * MatrixControl.FarPlaneSize().y/2.0f ) - ( X * MatrixControl.FarPlaneSize().x/2.0f );
    mFTR = mFarCenter + ( mUp * MatrixControl.FarPlaneSize().y/2.0f ) + ( X * MatrixControl.FarPlaneSize().x/2.0f );
    mFBL = mFarCenter - ( mUp * MatrixControl.FarPlaneSize().y/2.0f ) - ( X * MatrixControl.FarPlaneSize().x/2.0f );
    mFBR = mFarCenter - ( mUp * MatrixControl.FarPlaneSize().y/2.0f ) + ( X * MatrixControl.FarPlaneSize().x/2.0f );
    mNTL = mNearCenter + ( mUp * MatrixControl.NearPlaneSize().y / 2.0f ) - ( X * MatrixControl.NearPlaneSize().x/2.0f );
    mNTR = mNearCenter + ( mUp * MatrixControl.NearPlaneSize().y / 2.0f ) + ( X * MatrixControl.NearPlaneSize().x/2.0f );
    mNBL = mNearCenter - ( mUp * MatrixControl.NearPlaneSize().y / 2.0f ) - ( X * MatrixControl.NearPlaneSize().x/2.0f );
    mNBR = mNearCenter - ( mUp * MatrixControl.NearPlaneSize().y / 2.0f ) + ( X * MatrixControl.NearPlaneSize().x/2.0f );
    mPlanes[TOP] = Plane3d( mNTR, mNTL, mFTL );
    mPlanes[BOTTOM] = Plane3d( mNBL, mNBR, mFBR );
    mPlanes[LEFT] = Plane3d( mNTL, mNBL, mFBL );
    mPlanes[RIGHT] = Plane3d( mNBR, mNTR, mFBR );
    mPlanes[NEAR] = Plane3d( mNTL, mNTR, mNBR );
    mPlanes[FAR] = Plane3d( mFTR, mFTL, mFBL );
}

void Frustrum::Draw()
{
    std::vector<glm::vec3> mPositionsList;
    mPositionsList.push_back( mNTL );
    mPositionsList.push_back( mNBL );
    mPositionsList.push_back( mNTR );
    mPositionsList.push_back( mNTR );
    mPositionsList.push_back( mNBL );
    mPositionsList.push_back( mNBR );
    mPositionsList.push_back( mFTL );
    mPositionsList.push_back( mFBL );
    mPositionsList.push_back( mNTR );
    mPositionsList.push_back( mFTR );
    mPositionsList.push_back( mFBL );
    mPositionsList.push_back( mFBR );
    mPositionsList.push_back( mNTL );
    mPositionsList.push_back( mNBL );
    mPositionsList.push_back( mFTL );
    mPositionsList.push_back( mFTL );
    mPositionsList.push_back( mNBL );
    mPositionsList.push_back( mFBL );
    mPositionsList.push_back( mFTR );
    mPositionsList.push_back( mFBR );
    mPositionsList.push_back( mNTR );
    mPositionsList.push_back( mNTR );
    mPositionsList.push_back( mFBR );
    mPositionsList.push_back( mNBR );
    mPositionsList.push_back( mNTL );
    mPositionsList.push_back( mFTL );
    mPositionsList.push_back( mNTR );
    mPositionsList.push_back( mNTR );
    mPositionsList.push_back( mFTL );
    mPositionsList.push_back( mFTR );
    mPositionsList.push_back( mFBL );
    mPositionsList.push_back( mNBL );
    mPositionsList.push_back( mFBR );
    mPositionsList.push_back( mFBR );
    mPositionsList.push_back( mNBL );
    mPositionsList.push_back( mNBR );
    mPositionsList.push_back( mNTL );
    mPositionsList.push_back( mNTR );
    mPositionsList.push_back( mNTR );
    mPositionsList.push_back( mNBR );
    mPositionsList.push_back( mNBR );
    mPositionsList.push_back( mNBL );
    mPositionsList.push_back( mNBL );
    mPositionsList.push_back( mNTL );
    mPositionsList.push_back( mFTL );
    mPositionsList.push_back( mFTR );
    mPositionsList.push_back( mFTR );
    mPositionsList.push_back( mFBR );
    mPositionsList.push_back( mFBR );
    mPositionsList.push_back( mFBL );
    mPositionsList.push_back( mFBL );
    mPositionsList.push_back( mFTL );
    mPositionsList.push_back( mNTL );
    mPositionsList.push_back( mFTL );
    mPositionsList.push_back( mNTR );
    mPositionsList.push_back( mFTR );
    mPositionsList.push_back( mNBL );
    mPositionsList.push_back( mFBL );
    mPositionsList.push_back( mNBR );
    mPositionsList.push_back( mFBR );
    glm::mat4 mvp = MatrixControl.PerspectiveView();
    mPositionBuffer.AddVectorData( mPositionsList, sizeof( glm::vec3 ) );
    //Draw the frustrum from both sides
    glDisable( GL_CULL_FACE );
    mPositionBuffer.SetAttributeIndex( mShaderTransparent->GetAttribute( "Position" ) );
    mShaderTransparent->Bind();
    glUniformMatrix4fv( mShaderTransparent->GetUniform( "MVP" ), 1, GL_FALSE, &mvp[0][0] );
    mPositionBuffer.Bind( 3 );
    glDrawArrays ( GL_TRIANGLES, 0, 36 );
    mPositionBuffer.Unbind();
    Shader::Unbind();
    glEnable( GL_CULL_FACE );
    mPositionBuffer.SetAttributeIndex( mShader->GetAttribute( "Position" ) );
    mShader->Bind();
    glUniformMatrix4fv( mShader->GetUniform( "MVP" ), 1, GL_FALSE, &mvp[0][0] );
    mPositionBuffer.Bind( 3 );
    glDrawArrays ( GL_LINES, 36, 24 );
    mPositionBuffer.Unbind();
    Shader::Unbind();
}

