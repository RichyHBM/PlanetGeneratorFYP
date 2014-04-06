#include "Utilities.hpp"
#include <ctime>
#include <sys/stat.h>

#include "Managers/LogManager.hpp"

//Gets the last time a file was modified, it was going to be used for hotloading files
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

    //Get all errors in the error log
    while( ec != GL_NO_ERROR ) {
        switch( ec ) {
            case GL_INVALID_ENUM:
                Log.Warning( "OpenGL Error: GL_INVALID_ENUM from line " + Util::ToString( line ) + " in file" + Util::ToString( file ) );
                break;

            case GL_INVALID_VALUE:
                Log.Warning( "OpenGL Error: GL_INVALID_VALUE from line " + Util::ToString( line ) + " in file" + Util::ToString( file ) );
                break;

            case GL_INVALID_OPERATION:
                Log.Warning( "OpenGL Error: GL_INVALID_OPERATION from line " + Util::ToString( line ) + " in file" + Util::ToString( file ) );
                break;

            case GL_STACK_OVERFLOW:
                Log.Warning( "OpenGL Error: GL_STACK_OVERFLOW from line " + Util::ToString( line ) + " in file" + Util::ToString( file ) );
                break;

            case GL_STACK_UNDERFLOW:
                Log.Warning( "OpenGL Error: GL_STACK_UNDERFLOW from line " + Util::ToString( line ) + " in file" + Util::ToString( file ) );
                break;

            case GL_OUT_OF_MEMORY:
                Log.Warning( "OpenGL Error: GL_OUT_OF_MEMORY from line "  + Util::ToString( line ) + " in file" + Util::ToString( file ) );
                break;

            case GL_TABLE_TOO_LARGE:
                Log.Warning( "OpenGL Error: GL_TABLE_TOO_LARGE from line " + Util::ToString( line ) + " in file" + Util::ToString( file ) );
                break;

            default:
                Log.Warning( "Unknown OpenGL error from line " + Util::ToString( line ) + " in file" + Util::ToString( file ) );
        }

        ec = glGetError ();
    }
}

//Gets the current system time in a specific format
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
