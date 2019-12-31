#include <GL/glew.h>

#include "VertexBuffer.h"
#include "error_handling.h"


VertexBuffer::VertexBuffer(const float* data, unsigned int size)
{
    GLCall(glGenBuffers(1, &m_RendererId));
    Bind();
    GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}

VertexBuffer::~VertexBuffer()
{
    GLCall(glDeleteBuffers(1, &m_RendererId));
}

void VertexBuffer::Bind() const 
{
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererId));
}

void VertexBuffer::Unbind() const 
{
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

void VertexBufferLayout::Push(const VertexBufferLayoutElement& element)
{
    m_Elements.push_back(element);
    m_Stride += element.count * VertexBufferLayoutElement::GetSizeOfType(element.type);
}