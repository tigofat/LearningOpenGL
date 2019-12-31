#include <GL/glew.h>
#include <iostream>


void GLClearError()
{
    while (glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char* functionName, const char* fileName, int line)
{
    while (GLenum error = glGetError())
    {
        std::cout << "[OpenGL Error] (" << error << "): " << 
        functionName << " " << fileName << ":" << line << std::endl;
        return false;
    }
    return true;
}