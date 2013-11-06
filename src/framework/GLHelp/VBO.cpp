#include "VBO.hpp"
#include "../Utilities.hpp"

VBO::VBO()
{
    glGenBuffers( 1, &mBufferID );
	Util::PrintGLErrors();
    mHasTarget = false;
}

VBO::~VBO()
{
    glDeleteBuffers( 1, &mBufferID );
	Util::PrintGLErrors();
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
		Util::PrintGLErrors();
    }

    glBindBuffer( mTarget, mBufferID );
	Util::PrintGLErrors();

    if( mTarget == GL_ARRAY_BUFFER ) {
        glVertexAttribPointer( mAttributeIndex, pSize, pType, pNormalized, pStride, ( void * )0 );
		Util::PrintGLErrors();
    }
}

void VBO::Unbind()
{
    if( mTarget == GL_ARRAY_BUFFER ) {
        glDisableVertexAttribArray( mAttributeIndex );
		Util::PrintGLErrors();
    }
}
