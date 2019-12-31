#include <GL/glew.h>

#include "VertexArray.h"
#include "error_handling.h"


VertexArray::VertexArray()
{
    GLCall(glGenVertexArrays(1, &m_RendererId));
    GLCall(glBindVertexArray(m_RendererId));
}

VertexArray::~VertexArray()
{
    GLCall(glDeleteVertexArrays(1, &m_RendererId));
}

void VertexArray::AddBuffer(const VertexBuffer& buffer, const VertexBufferLayout& layout)
{
    Bind();
    buffer.Bind();
    const auto& elements = layout.GetElements();
    int offset = 0;

    for (int i = 0; i < layout.Size(); i++) 
    {
        const auto& element = elements[i];
        GLCall(glEnableVertexAttribArray(i));
        GLCall(glVertexAttribPointer(i, element.count, element.type, element.normalized, 
            layout.GetStride(), (const void*) offset));
        offset += VertexBufferLayoutElement::GetSizeOfType(element.type) * element.count;
    }
}

void VertexArray::Bind() const
{
    GLCall(glBindVertexArray(m_RendererId));
}

void VertexArray::Unbind() const
{
    GLCall(glBindVertexArray(0));
}