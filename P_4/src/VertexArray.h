#pragma once
#include "VertexBuffer.h"
class VertexBufferLayout;  //ǰ������ ��ص�ͷ�ļ�����cpp������

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