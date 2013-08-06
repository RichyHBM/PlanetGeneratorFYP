#ifndef SHADER_HPP
#define SHADER_HPP

#include "../Includes.hpp"

class Shader
{
public:
    ///
    ///Default constructor
    ///
    Shader();
    ///
    ///Default destructor
    ///
    ~Shader();
    ///
    ///Get the shaders ID
    ///
    GLuint GetShaderID();
    ///
    ///Load shaders from files
    ///
    bool LoadShaderFiles( const std::string &pVertFileName, const std::string &pFragFileName );
    ///
    ///Load shaders from code
    ///
    bool LoadShaderCode( const std::string &pVertCode, const std::string &pFragCode );
    ///
    ///Bind the shader
    ///
    void Bind();
    ///
    ///Unbind all shaders
    ///
    static void Unbind();
    ///
    ///Get a given attributes ID
    ///
    GLuint GetAttribute( const std::string &pAttName );
    ///
    ///Get a given uniforms ID
    ///
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
