#include "DebugLines.hpp"

DebugLines::DebugLines()
{
    mCameraMatrix = NULL;
    mPerspectiveMatrix = NULL;
    mMVP = glm::mat4( 1.0f );
    std::string vertCode =
        "#version 120\n" \
        "uniform mat4 MVP;\n" \
        "attribute vec3 Position;\n" \
        "attribute vec3 Color;\n" \
        "varying vec3 color;\n" \
        "void main(){\n" \
        "color = Color;\n" \
        "gl_Position =  MVP * vec4(Position, 1.0f);\n" \
        "}";
    std::string fragCode =
        "#version 120\n" \
        "varying vec3 color;\n" \
        "void main(){\n" \
        "gl_FragColor = vec4(color, 1.0f);\n" \
        "}";
    mLineShader.LoadShaderCode( vertCode, fragCode );
    mLineShader.Bind();
    mPositionBuffer.SetAttributeIndex( mLineShader.GetAttribute( "Position" ) );
    mColorBuffer.SetAttributeIndex( mLineShader.GetAttribute( "Color" ) );
    Shader::Unbind();
}

DebugLines::~DebugLines()
{
}

void DebugLines::SetCameraMatrix( glm::mat4 &pCameraMatrix )
{
    mCameraMatrix = &pCameraMatrix;

    if( mPerspectiveMatrix != NULL ) {
        mMVP = ( *mPerspectiveMatrix ) * ( *mCameraMatrix );
    }
}

void DebugLines::SetPerspectiveMatrix( glm::mat4 &pPerspectiveMatrix )
{
    mPerspectiveMatrix = &pPerspectiveMatrix;

    if( mCameraMatrix != NULL ) {
        mMVP = ( *mPerspectiveMatrix ) * ( *mCameraMatrix );
    }
}

void DebugLines::AddLines ( const glm::vec3 &pVecA, const glm::vec3 &pVecB, const glm::vec3 &pColor )
{
    mPositionsList.push_back ( pVecA.x );
    mPositionsList.push_back ( pVecA.y );
    mPositionsList.push_back ( pVecA.z );
    mVerticieAmount++;
    mPositionsList.push_back ( pVecB.x );
    mPositionsList.push_back ( pVecB.y );
    mPositionsList.push_back ( pVecB.z );
    mVerticieAmount++;
    mColorsList.push_back ( pColor.x );
    mColorsList.push_back ( pColor.y );
    mColorsList.push_back ( pColor.z );
    mColorsList.push_back ( pColor.x );
    mColorsList.push_back ( pColor.y );
    mColorsList.push_back ( pColor.z );
}

void DebugLines::AddTriangle ( const glm::vec3 &pVecA, const glm::vec3 &pVecB, const glm::vec3 &pVecC, const glm::vec3 &pColor )
{
    AddLines ( pVecA, pVecB, pColor );
    AddLines ( pVecB, pVecC, pColor );
    AddLines ( pVecC, pVecA, pColor );
}

void DebugLines::AddQuad ( const glm::vec3 &pVecA, const glm::vec3 &pVecB, const glm::vec3 &pVecC, const glm::vec3 &pVecD, const glm::vec3 &pColor )
{
    AddLines ( pVecA, pVecB, pColor );
    AddLines ( pVecB, pVecC, pColor );
    AddLines ( pVecC, pVecD, pColor );
    AddLines ( pVecD, pVecA, pColor );
}

void DebugLines::Draw()
{
    mLineShader.Bind ();
    glUniformMatrix4fv( mLineShader.GetUniform ( "MVP" ), 1, GL_FALSE, &mMVP[0][0] );
    mPositionBuffer.Bind ( 3 );
    mPositionBuffer.AddData ( mPositionsList, sizeof( float ), GL_ARRAY_BUFFER, GL_STREAM_DRAW );
    mColorBuffer.Bind ( 3 );
    mColorBuffer.AddData ( mColorsList, sizeof( float ), GL_ARRAY_BUFFER, GL_STREAM_DRAW );
    glDrawArrays ( GL_LINES, 0, mVerticieAmount );
    mColorBuffer.Unbind ();
    mPositionBuffer.Unbind ();
    Shader::Unbind ();
    mPositionsList.clear ();
    mColorsList.clear ();
    mVerticieAmount = 0;
}
