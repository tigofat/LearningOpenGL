#include <GL/glew.h>

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

#include "Shaders.h"


// unsigned int CompileShader(unsigned int type, const std::string source) {
//     unsigned int shaderId = glCreateShader(type);
//     const char* src = source.c_str();
//     glShaderSource(shaderId, 1, &src, nullptr);
//     glCompileShader(shaderId);

//     // error handling
//     int result;
//     glGetShaderiv(shaderId, GL_COMPILE_STATUS, &result);
    
//     if (result == GL_FALSE) {
//         int length;
//         glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &length);
//         char* message = (char*) alloca(length * sizeof(char));
//         glGetShaderInfoLog(shaderId, length, &length, message);
//         std::cout << "Failed to compile " << 
//         (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader" << std::endl;
//         std::cout << message << std::endl;
//         glDeleteShader(shaderId);

//         return 0;
//     }

//     return shaderId;
// }

// unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader) {
//     unsigned int program = glCreateProgram();
//     unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
//     unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

//     glAttachShader(program, vs);
//     glAttachShader(program, fs);
//     glLinkProgram(program);
//     glValidateProgram(program);

//     glDeleteShader(vs);
//     glDeleteShader(fs);

//     return program;
// }

bool Shader::Compile() const
{
    glShaderSource(m_RendererId, 1, &m_Source, nullptr);
    glCompileShader(m_RendererId);

    // error handling
    int result;
    glGetShaderiv(m_RendererId, GL_COMPILE_STATUS, &result);
    
    if (result == GL_FALSE) {
        int length;
        glGetShaderiv(m_RendererId, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*) alloca(length * sizeof(char));
        glGetShaderInfoLog(m_RendererId, length, &length, message);
        std::cout << "Failed to compile " << 
        (m_Type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader" << std::endl;
        std::cout << message << std::endl;
        this->~Shader();

        return false;
    }
    return true;
}

ShaderProgramSource ParseShader(const std::string& filePath)
{
    std::ifstream stream(filePath);

    if (stream.bad()) 
    {
        std::cout << filePath + std::string {" failed to open."} << std::endl;
    }

    enum class ShaderType {
        NONE = -1, VERTEX = 0, FRAGMENT = 1 
    };

    std::string line {};
    std::stringstream shaders[2];
    ShaderType type = ShaderType::NONE;

    while (std::getline(stream, line)) {
        if (line.find("#shader") != std::string::npos) {
            if (line.find("vertex") != std::string::npos) {
                // set mode to vertex
                type = ShaderType::VERTEX;
            } else if (line.find("fragment") != std::string::npos) {
                // set mode to fragment
                type = ShaderType::FRAGMENT;
            }
        }
        else {
            // shaders[static_cast<int> (type)].write(line.c_str(), line.length);
            // shaders[static_cast<int> (type)].write("\n", 1);
            shaders[(int) type] << line << "\n";
        }
    }

    return ShaderProgramSource { shaders[0].str(), shaders[1].str() };
}