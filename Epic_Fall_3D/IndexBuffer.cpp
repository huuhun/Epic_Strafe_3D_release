#include <glad/glad.h>
#include "IndexBuffer.h"

IndexBuffer::IndexBuffer()
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

void IndexBuffer::BufferData(const void* data) const {
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(data), data, GL_STATIC_DRAW);
}