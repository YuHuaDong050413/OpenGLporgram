#pragma once


class VertexBuffer
{
private:
	unsigned int m_RendererID;
public:
	VertexBuffer(const void* data, unsigned int count);
	~VertexBuffer();

	void Bind() const;
	void Unbind() const;
};