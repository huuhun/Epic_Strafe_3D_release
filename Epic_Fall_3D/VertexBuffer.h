#pragma once
#include <glad/glad.h>
class VertexBuffer {

public:
	VertexBuffer();
	~VertexBuffer();

	void Bind() const;
	void Unbind() const;

	void BufferData(const void* data, const GLuint& numElements) const;

	GLuint m_ID;
};