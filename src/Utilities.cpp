#include "Utilities.hpp"


void PrintGLErrors()
{
    GLuint ec = glGetError ();
    while(ec != GL_NO_ERROR) {
        std::cout << ec << std::endl;
        ec = glGetError ();
    }
}

