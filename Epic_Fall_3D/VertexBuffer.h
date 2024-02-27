#include <glad/glad.h>
#pragma once
class VertexBuffer {

public:
	VertexBuffer();
	~VertexBuffer();

	void Bind() const;
	void Unbind() const;

	void BufferData(const void* data, GLsizei size) const;

private:
	unsigned int m_ID;
};