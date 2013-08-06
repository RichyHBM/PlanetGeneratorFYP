#include "Utilities.hpp"
#include <ctime>
#include <sys/stat.h>



time_t Util::GetModificationTime( const std::string &filename )
{
    time_t elapsedSinceTimeStamp = 0;
    struct stat attrib;
    stat( filename.c_str(), &attrib );
    elapsedSinceTimeStamp = attrib.st_mtime;
    return elapsedSinceTimeStamp;
}

void Util::PrintGLErrorsFromLine( const char *file, int line = 0 )
{
    GLuint ec = glGetError ();

    while( ec != GL_NO_ERROR ) {
        switch( ec ) {
            case GL_INVALID_ENUM:
                std::cerr << "OpenGL Error: GL_INVALID_ENUM from line " << line << " in file" << file << std::endl;
                break;

            case GL_INVALID_VALUE:
                std::cerr << "OpenGL Error: GL_INVALID_VALUE from line " << line << " in file" << file << std::endl;
                break;

            case GL_INVALID_OPERATION:
                std::cerr << "OpenGL Error: GL_INVALID_OPERATION from line " << line << " in file" << file << std::endl;
                break;

            case GL_STACK_OVERFLOW:
                std::cerr << "OpenGL Error: GL_STACK_OVERFLOW from line " << line << " in file" << file << std::endl;
                break;

            case GL_STACK_UNDERFLOW:
                std::cerr << "OpenGL Error: GL_STACK_UNDERFLOW from line " << line << " in file" << file << std::endl;
                break;

            case GL_OUT_OF_MEMORY:
                std::cerr << "OpenGL Error: GL_OUT_OF_MEMORY from line " << line << " in file" << file << std::endl;
                break;

            case GL_TABLE_TOO_LARGE:
                std::cerr << "OpenGL Error: GL_TABLE_TOO_LARGE from line " << line << " in file" << file << std::endl;
                break;

            default:
                std::cerr << "Unknown OpenGL error from line " << line << " in file" << file << std::endl;
        }

        ec = glGetError ();
    }
}

std::string Util::GetLocalDateTime( const std::string &format )
{
    const int bufferSize = 80;
    char buffer[bufferSize];
    time_t rawtime;
    struct tm *timeinfo;
    time ( &rawtime );
    timeinfo = localtime ( &rawtime );
    strftime ( buffer, bufferSize, format.c_str() , timeinfo );
    return std::string( buffer );
}
