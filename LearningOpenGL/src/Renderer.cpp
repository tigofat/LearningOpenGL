#include <GL/glew.h>

#include "Renderer.h"
#include "error_handling.h"


void Renderer::Clear() const
{
    GLCall(glClear(GL_COLOR_BUFFER_BIT));
}

void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const ShaderProgram& program) const
{
    program.Bind();

    va.Bind();
    ib.Bind();

    GLCall(glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr));
}