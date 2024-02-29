#pragma once
#include <glad/glad.h>
class IndexBuffer {

private:
	GLuint m_ID;
public:
	IndexBuffer();
	~IndexBuffer();

	void Bind() const;
	void Unbind() const;
	void BufferData(const void* data, const GLuint& numElements) const;
};