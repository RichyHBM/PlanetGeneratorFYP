#include "Utilities.hpp"
#include <ctime>

void Util::PrintGLErrors()
{
    GLuint ec = glGetError ();
    while(ec != GL_NO_ERROR) {
        std::cout << ec << std::endl;
        ec = glGetError ();
    }
}

std::string Util::GetLocalDateTime(const std::string &format)
{
	const int bufferSize = 80;
    char buffer[bufferSize];
    time_t rawtime;
    struct tm * timeinfo;

    time (&rawtime);
    timeinfo = localtime (&rawtime);
    strftime (buffer, bufferSize, format.c_str() , timeinfo);
    return std::string(buffer);
}
