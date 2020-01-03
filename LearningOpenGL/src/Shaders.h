#pragma once

#include <iostream>
#include <unordered_map>

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

private:
    bool Compile() const;

public:
    Shader(unsigned int type, const char* source)
    : m_Type(type), m_Source((char*) source) {
        m_RendererId = glCreateShader(type);
        Compile();
    }
    ~Shader() { GLCall(glDeleteShader(m_RendererId)); }

    unsigned int GetRendererId() const { return m_RendererId; }

    unsigned int GetType() const { return m_Type; }
};

class ShaderProgram
{
private:
    unsigned int m_RendererId;
    std::unordered_map<std::string, int> m_UniformLocationCache;
public:
    ShaderProgram() 
    { 
        m_RendererId = glCreateProgram();
    }

    ~ShaderProgram() { GLCall(glDeleteProgram(m_RendererId)); }

    void AttachShader(const Shader& shader) { GLCall(glAttachShader(m_RendererId, shader.GetRendererId())); }

    void Link();

    int GetUniformLocation(const std::string& uniformVariableName);

    void SetUniform1i(const std::string& name, int slot);
    void SetUniform1f(const std::string& name, float v);
    void SetUnifrom4f(const std::string& name, float v0, float v1, float v2, float v3);

    void Bind() const { GLCall(glUseProgram(m_RendererId)); }
    void Unbind() const { GLCall(glUseProgram(0)); };

    unsigned int GetRendererId() { return m_RendererId; }
};