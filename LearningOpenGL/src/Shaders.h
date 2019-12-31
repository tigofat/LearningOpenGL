#pragma once

#include "error_handling.h"


struct ShaderProgramSource {
    std::string VertexShader;
    std::string FragmentShader;
};

ShaderProgramSource ParseShader(const std::string& filePath);

class Shader
{
private:
    unsigned int m_RendererId;
    unsigned int m_Type;
    char* m_Source;

    bool Compile() const;
public:
    Shader(unsigned int type, const char* source)
    : m_Type(type), m_Source((char*) source) {
        m_RendererId = glCreateShader(type);
        Compile();
    }
    ~Shader() { GLCall(glDeleteShader(m_RendererId)); }

    // void Bind() const;
    // void Unbind() const;

    unsigned int GetRendererId() const { return m_RendererId; }

    unsigned int GetType() const { return m_Type; }
};

class ShaderProgram
{
private:
    unsigned int m_RendererId;
public:
    ShaderProgram() 
    { 
        m_RendererId = glCreateProgram();
        Bind();
    }

    ~ShaderProgram() { GLCall(glDeleteProgram(m_RendererId)); }

    void AttachShader(const Shader& shader) { GLCall(glAttachShader(m_RendererId, shader.GetRendererId())); }

    void Link() 
    { 
        GLCall(glLinkProgram(m_RendererId));
        GLCall(glValidateProgram(m_RendererId)); 
    }

    void Bind() const { GLCall(glUseProgram(m_RendererId)); }
    void Unbind() const { GLCall(glUseProgram(0)); };

    unsigned int GetRendererId() { return m_RendererId; }
};