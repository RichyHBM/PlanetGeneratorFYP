#ifndef VBO_HPP
#define VBO_HPP

#include "../Includes.hpp"

class VBO
{
public:
    VBO();
    ~VBO();
    GLuint GetBufferID();

    //Set the shader attribute index for the data
    void SetAttributeIndex( GLuint pAttribIndex );
    
    void Bind( GLint pSize = 0, GLenum pType = GL_FLOAT , GLboolean pNormalized = false, GLsizei pStride = 0 );
    void Unbind();

    //Set the type of VBO
    void SetTarget( GLenum pTarget = GL_ARRAY_BUFFER );

    //Add the data using a vector
    template <class T>
    void AddData( std::vector<T> &pData, GLuint pSize, GLenum pTarget = GL_ARRAY_BUFFER, GLenum mUsageHint = GL_STATIC_DRAW ) {
        if( !mHasTarget ) {
            mHasTarget = true;
            mTarget = pTarget;
        }

        glBindBuffer( mTarget, mBufferID );
        glBufferData( mTarget, pData.size() * pSize , &pData[0] , mUsageHint );
    }

    //Set the data using an array
    template <class T>
    void AddData( T &pData, int pAmount, GLuint pSize, GLenum pTarget = GL_ARRAY_BUFFER, GLenum mUsageHint = GL_STATIC_DRAW ) {
        if( !mHasTarget ) {
            mHasTarget = true;
            mTarget = pTarget;
        }

        glBindBuffer( mTarget, mBufferID );
        glBufferData( mTarget, pAmount * pSize , &pData , mUsageHint );
    }

protected:
private:
    bool mHasTarget;
    GLuint mBufferID;
    GLenum mTarget;
    GLuint mAttributeIndex;
};

#endif // VBO_HPP
