#pragma once
#include <vector>
#include <GL/glew.h>
#include "Renderer.h"

struct VertexBufferElement
{
	unsigned int type;
	unsigned int count;
	unsigned char normalized;

	static unsigned int GetSizeOfType(unsigned int type)
	{
		switch (type)
		{
		case GL_FLOAT:			return sizeof(GLfloat);
		//case GL_INT:			return sizeof(GLint);
		case GL_DOUBLE:			return sizeof(GLdouble);
		case GL_UNSIGNED_INT:	return sizeof(GLuint);
		case GL_UNSIGNED_BYTE:	return sizeof(GLubyte);
		}
		ASSERT(false);
		return 0;
	}
};

class VertexBufferLayout
{
private:
	std::vector<VertexBufferElement> m_Elements;
	unsigned int m_Stride;

public:
	VertexBufferLayout()
		:m_Stride(0) {}

	template<typename T>
	void Push(unsigned int count)
	{
		//static_assert(false);
		static_assert(sizeof(T) == 0, "Unsupported type in VertexBufferLayout::Push");
	}
	template<>
	void Push<float>(unsigned int count)
	{
		m_Elements.push_back(VertexBufferElement(GL_FLOAT, count, GL_FALSE));
		m_Stride += count * VertexBufferElement::GetSizeOfType(GL_FLOAT);
	}
	template<>
	void Push<double>(unsigned int count)
	{
		m_Elements.push_back(VertexBufferElement(GL_DOUBLE, count, GL_FALSE));
		m_Stride += count * VertexBufferElement::GetSizeOfType(GL_DOUBLE);
	}
	template<>
	void Push<unsigned int>(unsigned int count)
	{
		m_Elements.push_back(VertexBufferElement(GL_UNSIGNED_INT, count, GL_FALSE));
		m_Stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_INT);
	}
	/*template<>
	void Push<int>(unsigned int count)
	{
		m_Elements.push_back(VertexBufferElement(GL_INT, count, GL_FALSE));
		m_Stride += count * VertexBufferElement::GetSizeOfType(GL_INT);
	}*/
	template<>
	void Push<unsigned char>(unsigned int count)
	{
		m_Elements.push_back(VertexBufferElement(GL_UNSIGNED_BYTE, count, GL_TRUE));
		m_Stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_BYTE);
	}
	inline const std::vector<VertexBufferElement> GetElement() const { return m_Elements; }
	inline unsigned int GetStride() const { return m_Stride; }
	
};

