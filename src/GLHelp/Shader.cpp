#include "../Utilities.hpp"
#include "Shader.hpp"

Shader::Shader()
{
    mShaderID = glCreateProgram();
    mVertexID = glCreateShader(GL_VERTEX_SHADER);
    mFragmentID = glCreateShader(GL_FRAGMENT_SHADER);
}

Shader::~Shader()
{
    glDeleteShader(mVertexID);
    glDeleteShader(mFragmentID);
    glDeleteProgram(mShaderID);
}

GLuint Shader::GetShaderID()
{
    return mShaderID;
}

void Shader::Bind()
{
    glUseProgram(mShaderID);
}

void Shader::Unbind()
{
    glUseProgram(0);
}

GLuint Shader::GetAttribute(const std::string &pAttName)
{
    std::map<std::string, GLuint>::iterator it = mAttributeVariableIDList.find(pAttName);
    if (it != mAttributeVariableIDList.end())
    {
        return it->second;
    }

    GLuint attribute = glGetAttribLocation(mShaderID, pAttName.c_str());
    mAttributeVariableIDList[pAttName] = attribute;
    return attribute;
}

GLuint Shader::GetUniform(const std::string &pUniName)
{
    std::map<std::string, GLuint>::iterator it = mUniformVariableIDList.find(pUniName);
    if (it != mUniformVariableIDList.end())
    {
        return it->second;
    }

    GLuint uniform = glGetUniformLocation(mShaderID, pUniName.c_str());
    mUniformVariableIDList[pUniName] = uniform;
    return uniform;
}

bool Shader::linkShader()
{
    GLint Result = GL_FALSE;
    int InfoLogLength;

    /// Link the program
    //fprintf(stdout, "Linking program ");
    glAttachShader(mShaderID, mVertexID);
    glAttachShader(mShaderID, mFragmentID);
    glLinkProgram(mShaderID);

    /// Check the program
    glGetProgramiv(mShaderID, GL_LINK_STATUS, &Result);
    glGetProgramiv(mShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    std::vector<char> ProgramErrorMessage( MaxValue(InfoLogLength, 1) );
    glGetProgramInfoLog(mShaderID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
    if(Result == GL_FALSE)
        fprintf(stdout, "%s\n", &ProgramErrorMessage[0]);

    if(Result == GL_TRUE) return true;
    else return false;
}

bool Shader::compileVertexShader(const std::string &pVertCode)
{
    GLint Result = GL_FALSE;
    int InfoLogLength;

    /// Compile Vertex Shader
    //printf("Compiling shader : %s ", vertFileName.c_str());
    char const * VertexSourcePointer = pVertCode.c_str();
    glShaderSource(mVertexID, 1, &VertexSourcePointer , NULL);
    glCompileShader(mVertexID);

    /// Check Vertex Shader
    glGetShaderiv(mVertexID, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(mVertexID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    std::vector<char> VertexShaderErrorMessage(InfoLogLength);
    glGetShaderInfoLog(mVertexID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
    if(Result == GL_FALSE)
        fprintf(stdout, "%s\n", &VertexShaderErrorMessage[0]);

    if(Result == GL_TRUE) return true;
    else return false;
}

bool Shader::compileFragmentShader(const std::string &pFragCode)
{
    GLint Result = GL_FALSE;
    int InfoLogLength;

    /// Compile Fragment Shader
    //printf("Compiling shader : %s ", fragFileName.c_str());
    char const * FragmentSourcePointer = pFragCode.c_str();
    glShaderSource(mFragmentID, 1, &FragmentSourcePointer , NULL);
    glCompileShader(mFragmentID);

    /// Check Fragment Shader
    glGetShaderiv(mFragmentID, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(mFragmentID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    std::vector<char> FragmentShaderErrorMessage(InfoLogLength);
    glGetShaderInfoLog(mFragmentID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
    if(Result == GL_FALSE)
        fprintf(stdout, "%s\n", &FragmentShaderErrorMessage[0]);

    if(Result == GL_TRUE) return true;
    else return false;
}

bool Shader::LoadShaderCode(const std::string &pVertCode, const std::string &pFragCode)
{
    mAttributeVariableIDList.clear();
    mUniformVariableIDList.clear();

    bool result = true;

    if(result) result = compileVertexShader(pVertCode);
    if(result) result = compileFragmentShader(pFragCode);
    if(result) result = linkShader();
    return result;
}

bool Shader::LoadShaderFiles(const std::string &pVertFileName, const std::string &pFragFileName)
{
    /// Read the Vertex Shader code from the file
    std::string VertexShaderCode;
    std::string FragmentShaderCode;

    bool filesWork = true;
    try
    {
        std::ifstream VertexShaderStream(pVertFileName.c_str(), std::ios::in);
        if(VertexShaderStream.is_open())
        {
            std::string Line = "";
            while(getline(VertexShaderStream, Line))
                VertexShaderCode += "\n" + Line;
            VertexShaderStream.close();
        }
    }
    catch(int e)
    {
        std::cout << "Error opening: " << pVertFileName << " : " << e << std::endl;
        filesWork = false;
    }

    try
    {
        /// Read the Fragment Shader code from the file

        std::ifstream FragmentShaderStream(pFragFileName.c_str(), std::ios::in);
        if(FragmentShaderStream.is_open())
        {
            std::string Line = "";
            while(getline(FragmentShaderStream, Line))
                FragmentShaderCode += "\n" + Line;
            FragmentShaderStream.close();
        }
    }
    catch(int e)
    {
        std::cout << "Error opening: " << pFragFileName << " : " << e << std::endl;
        filesWork=false;
    }

    if(filesWork == false)
    {
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

    return LoadShaderCode(VertexShaderCode, FragmentShaderCode);

}
