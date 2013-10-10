#include "VBO.hpp"

VBO::VBO()
{
    glGenBuffers( 1, &mBufferID );
    mHasTarget = false;
}

VBO::~VBO()
{
    glDeleteBuffers( 1, &mBufferID );
}

GLuint VBO::GetBufferID()
{
    return mBufferID;
}

void VBO::SetTarget( GLenum pTarget )
{
    mTarget = pTarget;
    mHasTarget = true;
}

void VBO::SetAttributeIndex( GLuint pAttribIndex )
{
    mAttributeIndex = pAttribIndex;
}

void VBO::Bind( GLint pSize, GLenum pType , GLboolean pNormalized, GLsizei pStride )
{
    if( !mHasTarget ) {
        SetTarget();
    }

    if( mTarget == GL_ARRAY_BUFFER ) {
        glEnableVertexAttribArray( mAttributeIndex );
    }

    glBindBuffer( mTarget, mBufferID );

    if( mTarget == GL_ARRAY_BUFFER ) {
        glVertexAttribPointer( mAttributeIndex, pSize, pType, pNormalized, pStride, ( void * )0 );
    }
}

void VBO::Unbind()
{
    if( mTarget == GL_ARRAY_BUFFER ) {
        glDisableVertexAttribArray( mAttributeIndex );
    }
}
