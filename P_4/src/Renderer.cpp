#include "Renderer.h"
#include <iostream>


void GlClearError()
{
	while (glGetError() != GL_NO_ERROR);
}

bool GLLogcall(const char* function, const char* file, int line)
{
	while (GLenum error = glGetError())
	{
		std::cout << "[OpenGL Error] (" << error << "): " << function << " " << file << " (" << line << ")" << std::endl;
		return false;
	}
	return true;
	
}

void Renderer::ClearColor(const std::array<float, 4>& color) const
{
	GLCall(glClearColor(color[0], color[1], color[2], color[3]));
	GLCall(glClear(GL_COLOR_BUFFER_BIT));
}

void Renderer::ClearDepth() const
{
	GLCall(glClear(GL_DEPTH_BUFFER_BIT));
}

void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const
{
	shader.Bind();
	va.Bind();
	ib.Bind();
	GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
}

