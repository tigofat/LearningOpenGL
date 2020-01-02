#pragma once

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shaders.h"


class Renderer
{
private:

public:
    void Renderer::Clear() const;

    void Draw(const VertexArray& va, const IndexBuffer& ib, const ShaderProgram& shader) const;
};