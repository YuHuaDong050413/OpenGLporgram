#pragma once
#include "VertexBuffer.h"
class VertexBufferLayout;  //前置声明 相关的头文件会在cpp中声明

class VertexArray
{
private:
	unsigned int m_RendererID;
public:
	VertexArray();
	~VertexArray();

	void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);
	void AddBufferOnlyPosition(const VertexBuffer& vb, const VertexBufferLayout& layout);


	void Bind() const;
	void Unbind() const;
};