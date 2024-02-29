#include <glad/glad.h>
#include "IndexBuffer.h"

IndexBuffer::IndexBuffer()
	:m_ID(0)
{
	glGenBuffers(1, &m_ID);
}

IndexBuffer::~IndexBuffer()
{
	glDeleteBuffers(1, &m_ID);
}

void IndexBuffer::Bind() const {

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID);
}

void IndexBuffer::Unbind() const {

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void IndexBuffer::BufferData(const void* data, const GLuint& numElements) const {
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, numElements * (GLsizeiptr)(sizeof(data)), data, GL_STATIC_DRAW);
}