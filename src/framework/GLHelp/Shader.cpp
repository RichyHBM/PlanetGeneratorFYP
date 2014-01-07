#include "../Utilities.hpp"
#include "Shader.hpp"

Shader::Shader()
{
    mShaderID = glCreateProgram();
    Util::PrintGLErrors();
    mVertexID = glCreateShader( GL_VERTEX_SHADER );
    Util::PrintGLErrors();
    mFragmentID = glCreateShader( GL_FRAGMENT_SHADER );
    Util::PrintGLErrors();
}

Shader::~Shader()
{
    glDeleteShader( mVertexID );
    Util::PrintGLErrors();
    glDeleteShader( mFragmentID );
    Util::PrintGLErrors();
    glDeleteProgram( mShaderID );
    Util::PrintGLErrors();
}

GLuint Shader::GetShaderID()
{
    return mShaderID;
}

void Shader::Bind()
{
    glUseProgram( mShaderID );
    Util::PrintGLErrors();
}

void Shader::Unbind()
{
    glUseProgram( 0 );
    Util::PrintGLErrors();
}

GLuint Shader::GetAttribute( const std::string &pAttName )
{
    std::map<std::string, GLuint>::iterator it = mAttributeVariableIDList.find( pAttName );

    if ( it != mAttributeVariableIDList.end() ) {
        return it->second;
    }

    GLuint attribute = glGetAttribLocation( mShaderID, pAttName.c_str() );
    Util::PrintGLErrors();
    mAttributeVariableIDList[pAttName] = attribute;
    return attribute;
}

GLuint Shader::GetUniform( const std::string &pUniName )
{
    std::map<std::string, GLuint>::iterator it = mUniformVariableIDList.find( pUniName );

    if ( it != mUniformVariableIDList.end() ) {
        return it->second;
    }

    GLuint uniform = glGetUniformLocation( mShaderID, pUniName.c_str() );
    Util::PrintGLErrors();
    mUniformVariableIDList[pUniName] = uniform;
    return uniform;
}

bool Shader::linkShader()
{
    GLint Result = GL_FALSE;
    int InfoLogLength = 0;
    /// Link the program
    glAttachShader( mShaderID, mVertexID );
    Util::PrintGLErrors();
    glAttachShader( mShaderID, mFragmentID );
    Util::PrintGLErrors();
    glLinkProgram( mShaderID );
    Util::PrintGLErrors();
    /// Check the program
    glGetProgramiv( mShaderID, GL_LINK_STATUS, &Result );
    Util::PrintGLErrors();
    glGetProgramiv( mShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength );
    Util::PrintGLErrors();
    std::vector<char> ProgramErrorMessage( Util::MaxValue( InfoLogLength, 1 ) );
    glGetProgramInfoLog( mShaderID, InfoLogLength, NULL, &ProgramErrorMessage[0] );
    Util::PrintGLErrors();

    if( Result == GL_FALSE ) {
        Log.Error( &ProgramErrorMessage[0] );
        return false;
    }

    return true;
}

bool Shader::compileVertexShader( const std::string &pVertCode )
{
    GLint Result = GL_FALSE;
    int InfoLogLength = 0;
    /// Compile Vertex Shader
    char const *VertexSourcePointer = pVertCode.c_str();
    glShaderSource( mVertexID, 1, &VertexSourcePointer , NULL );
    Util::PrintGLErrors();
    glCompileShader( mVertexID );
    Util::PrintGLErrors();
    /// Check Vertex Shader
    glGetShaderiv( mVertexID, GL_COMPILE_STATUS, &Result );
    Util::PrintGLErrors();
    glGetShaderiv( mVertexID, GL_INFO_LOG_LENGTH, &InfoLogLength );
    Util::PrintGLErrors();
    std::vector<char> VertexShaderErrorMessage( Util::MaxValue( InfoLogLength, 1 ) );
    glGetShaderInfoLog( mVertexID, InfoLogLength, NULL, &VertexShaderErrorMessage[0] );
    Util::PrintGLErrors();

    if( Result == GL_FALSE ) {
        Log.Error( &VertexShaderErrorMessage[0] );
        return false;
    }

    return true;
}

bool Shader::compileFragmentShader( const std::string &pFragCode )
{
    GLint Result = GL_FALSE;
    int InfoLogLength = 0;
    /// Compile Fragment Shader
    char const *FragmentSourcePointer = pFragCode.c_str();
    glShaderSource( mFragmentID, 1, &FragmentSourcePointer , NULL );
    Util::PrintGLErrors();
    glCompileShader( mFragmentID );
    Util::PrintGLErrors();
    /// Check Fragment Shader
    glGetShaderiv( mFragmentID, GL_COMPILE_STATUS, &Result );
    Util::PrintGLErrors();
    glGetShaderiv( mFragmentID, GL_INFO_LOG_LENGTH, &InfoLogLength );
    Util::PrintGLErrors();
    std::vector<char> FragmentShaderErrorMessage( Util::MaxValue( InfoLogLength, 1 ) );
    glGetShaderInfoLog( mFragmentID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0] );
    Util::PrintGLErrors();

    if( Result == GL_TRUE ) {
        return true;
    }

    Log.Error(  &FragmentShaderErrorMessage[0] );
    return false;
}

bool Shader::LoadShaderCode( const std::string &pVertCode, const std::string &pFragCode )
{
    mAttributeVariableIDList.clear();
    mUniformVariableIDList.clear();
    bool result = true;

    if( result ) {
        result = compileVertexShader( pVertCode );
    }

    if( result ) {
        result = compileFragmentShader( pFragCode );
    }

    if( result ) {
        result = linkShader();
    }

    return result;
}

bool Shader::LoadShaderFiles( const std::string &pVertFileName, const std::string &pFragFileName )
{
    /// Read the Vertex Shader code from the file
    std::string VertexShaderCode;
    std::string FragmentShaderCode;
    bool filesWork = true;

    try {
        std::ifstream VertexShaderStream( pVertFileName.c_str(), std::ios::in );

        if( VertexShaderStream.is_open() ) {
            std::string Line = "";

            while( getline( VertexShaderStream, Line ) ) {
                if( Line.size() > 9 && Line.compare( 0, 8, "#include" ) == 0 ) {
                    std::string fileLocation = Line.substr( 9, Line.size() - 9 );
                    VertexShaderCode += "\n" + LoadFile( fileLocation );

                } else {
                    VertexShaderCode += "\n" + Line;
                }
            }

            VertexShaderStream.close();
        }

        Log.Success( "Loaded: " + pVertFileName );

    } catch( int ) {
        Log.Error( " Failed to load: " + pVertFileName );
        filesWork = false;
    }

    try {
        /// Read the Fragment Shader code from the file
        std::ifstream FragmentShaderStream( pFragFileName.c_str(), std::ios::in );

        if( FragmentShaderStream.is_open() ) {
            std::string Line = "";

            while( getline( FragmentShaderStream, Line ) ) {
                if( Line.size() > 9 && Line.compare( 0, 8, "#include" ) == 0 ) {
                    std::string fileLocation = Line.substr( 9, Line.size() - 9 );
                    FragmentShaderCode += "\n" + LoadFile( fileLocation );

                } else {
                    FragmentShaderCode += "\n" + Line;
                }
            }

            FragmentShaderStream.close();
        }

        Log.Success( "Loaded: " + pFragFileName );

    } catch( int ) {
        Log.Error( " Failed to load: " + pFragFileName );
        filesWork=false;
    }

    if( filesWork == false ) {
        VertexShaderCode = "#version 120\n"
                           "uniform mat4 MVP;\n"
                           "attribute vec4 Position;\n"
                           "void main(){\n"
                           "gl_Position =  MVP * Position;\n"
                           "}";
        FragmentShaderCode = "#version 120\n"
                             "void main(){\n"
                             "gl_FragColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);\n"
                             "}";
    }

    return LoadShaderCode( VertexShaderCode, FragmentShaderCode );
}

std::string Shader::LoadFile( const std::string &pFile )
{
    std::string contents = "";

    try {
        std::ifstream fileStream( pFile.c_str(), std::ios::in );

        if( fileStream.is_open() ) {
            std::string Line = "";

            while( getline( fileStream, Line ) ) {
                if( Line.size() > 9 && Line.compare( 0, 8, "#include" ) == 0 ) {
                    std::string fileLocation = Line.substr( 9, Line.size() - 9 );
                    contents += "\n" + LoadFile( fileLocation );

                } else {
                    contents += "\n" + Line;
                }
            }

            fileStream.close();
        }

        Log.Success( "Loaded: " + pFile );

    } catch( int ) {
        Log.Error( " Failed to load: " + pFile );
        contents = "";
    }

    return contents;
}
