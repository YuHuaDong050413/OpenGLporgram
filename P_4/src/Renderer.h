#pragma once
#include <GL/glew.h>
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include <iostream>
#include <array>

#define ASSERT(x) if (!(x)) __debugbreak();
#define GLCall(x) GlClearError();\
    x;\
    ASSERT(GLLogcall(#x, __FILE__, __LINE__))

void GlClearError();
bool GLLogcall(const char* function, const char* file, int line);

class Renderer
{
public:
    void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
    void ClearColor(const std::array<float, 4>& color) const;
    void ClearDepth() const;
};