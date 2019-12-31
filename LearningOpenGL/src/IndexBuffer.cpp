#include <GL/glew.h>

#include "IndexBuffer.h"
#include "error_handling.h"


IndexBuffer::IndexBuffer(const unsigned int* indices, unsigned int count)
{
    // keep in mind that unsigned int can be not 4 bytes
    GLCall(glGenBuffers(1, &m_RendererId));
    Bind();
    GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), indices, GL_STATIC_DRAW));
}

IndexBuffer::~IndexBuffer()
{
    GLCall(glDeleteBuffers(1, &m_RendererId));
}

void IndexBuffer::Bind() const 
{
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererId));
}

void IndexBuffer::Unbind() const 
{
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}