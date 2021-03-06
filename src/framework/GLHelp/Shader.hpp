#ifndef SHADER_HPP
#define SHADER_HPP

#include "../Includes.hpp"

#define GLSL(src) "#version 120\n" #src

class Shader
{
public:
    Shader();
    ~Shader();
    GLuint GetShaderID();

    bool LoadShaderFiles( const std::string &pVertFileName, const std::string &pFragFileName );

    bool LoadShaderCode( const std::string &pVertCode, const std::string &pFragCode );

    std::string LoadFile( const std::string &pFile );

    void Bind();
    static void Unbind();

    //Get a given attributes ID
    GLuint GetAttribute( const std::string &pAttName );

    //Get a given uniforms ID
    GLuint GetUniform( const std::string &pUniName );
protected:
private:
    GLuint mShaderID;
    GLuint mVertexID;
    GLuint mFragmentID;
    std::map< std::string, GLuint > mUniformVariableIDList;
    std::map< std::string, GLuint > mAttributeVariableIDList;
    bool linkShader();
    bool compileVertexShader( const std::string &pVertCode );
    bool compileFragmentShader( const std::string &pFragCode );
};

#endif // SHADER_HPP
