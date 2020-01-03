#pragma once

#include <vector>
#include "error_handling.h" 


struct VertexBufferLayoutElement 
{
    unsigned int type;
    unsigned int count;
    unsigned char normalized;

    static unsigned int GetSizeOfType(unsigned int type) {
        switch (type)
        {
            case GL_FLOAT: return sizeof(float);
            case GL_UNSIGNED_INT: return sizeof(unsigned int);
            case GL_UNSIGNED_BYTE: return sizeof(unsigned char);
        }
        Assert(false);
        return 0;
    }
};

class VertexBufferLayout
{
private:
    std::vector<VertexBufferLayoutElement> m_Elements;
    int m_Stride = 0;
public:
    VertexBufferLayout() {};

    void Push(const VertexBufferLayoutElement&);

    const std::vector<VertexBufferLayoutElement>& GetElements() const { return m_Elements; }

    int Size() const { return m_Elements.size(); }

    int GetStride() const { return m_Stride; }
};

class VertexBuffer
{
private:
    unsigned int m_RendererId;
public:
    VertexBuffer(const float* data, unsigned int size);
    ~VertexBuffer();

    void Bind() const;
    void Unbind() const;
};