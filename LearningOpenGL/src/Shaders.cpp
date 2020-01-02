#include <GL/glew.h>

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

#include "Shaders.h"


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

int ShaderProgram::GetUniformLocation(const std::string& name)
{
    for (auto elem : m_UniformLocationCache)
    {
        if (elem.first == name)
            return m_UniformLocationCache[name];
    }

    GLCall(int location = glGetUniformLocation(m_RendererId, name.c_str()));
    Assert(location != -1);
    m_UniformLocationCache.insert({name, location});
    
    return location;
}

void ShaderProgram::SetUniform1i(const std::string& name, int slot)
{
    GLCall(glUniform1i(GetUniformLocation(name), slot));
}

void ShaderProgram::SetUnifrom4f(const std::string& name, float v0, float v1, float v2, float v3)
{        
    GLCall(glUniform4f(GetUniformLocation(name), v0, v1, v2, v3));
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