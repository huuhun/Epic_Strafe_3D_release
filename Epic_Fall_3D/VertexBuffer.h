#include <glad/glad.h>
#pragma once
class VertexBuffer {

public:
	VertexBuffer();
	~VertexBuffer();

	void Bind() const;
	void Unbind() const;

	void BufferData(GLsizei size, const void* data) const;

	unsigned int m_ID;
};