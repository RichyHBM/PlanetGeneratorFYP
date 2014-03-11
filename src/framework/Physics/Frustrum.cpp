#include "Frustrum.hpp"

#include "../Managers/MatrixManager.hpp"
#include "../Managers/ResourceManager.hpp"
#include "../Utilities.hpp"

Frustrum::Frustrum()
{
    int Dists[] = {500, 275, 150, 80, 40, 15};

    for( int i = 0; i < DISTANCES_AMOUNT; i++ ) {
        Distances[i] = Dists[i];
    }

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
    mPlanes[Top] = Plane3d( mNTR, mNTL, mFTL );
    mPlanes[Bottom] = Plane3d( mNBL, mNBR, mFBR );
    mPlanes[Left] = Plane3d( mNTL, mNBL, mFBL );
    mPlanes[Right] = Plane3d( mNBR, mNTR, mFBR );
    mPlanes[Near] = Plane3d( mNTL, mNTR, mNBR );
    mPlanes[Far] = Plane3d( mFTR, mFTL, mFBL );
}

Frustrum::~Frustrum()
{
    mShader = NULL;
}

glm::vec3 Frustrum::Position() const
{
    return mPosition;
}

bool Frustrum::InFrustrum( const glm::vec3 &point ) const
{
    for( int i = 0; i < 6; i++ ) {
        float distance = mPlanes[i].GetDistance( point );

        if ( mPlanes[i].GetDistance( point ) < 0.0f ) {
            return false;
        }
    }

    return true;
}

bool Frustrum::InFrustrumAndFacing( const Quad &quad ) const
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
    float normADot = glm::dot( -Z, quad.GetNormalA() );
    float normBDot = glm::dot( -Z, quad.GetNormalB() );

    if( normADot < 0.1f || normBDot < 0.1f ) {
        return true;
    }

    return false;
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
    mPlanes[Top] = Plane3d( mNTR, mNTL, mFTL );
    mPlanes[Bottom] = Plane3d( mNBL, mNBR, mFBR );
    mPlanes[Left] = Plane3d( mNTL, mNBL, mFBL );
    mPlanes[Right] = Plane3d( mNBR, mNTR, mFBR );
    mPlanes[Near] = Plane3d( mNTL, mNTR, mNBR );
    mPlanes[Far] = Plane3d( mFTR, mFTL, mFBL );
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

