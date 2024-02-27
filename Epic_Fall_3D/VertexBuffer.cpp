#include <glad/glad.h>
#include "VertexBuffer.h"

VertexBuffer::VertexBuffer() 
	: m_ID(0)
{
	glGenBuffers(1, &m_ID);
}

VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &m_ID);
}

void VertexBuffer::Bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_ID);
}

void VertexBuffer::Unbind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

// Fill the VBO with data
void VertexBuffer::BufferData(const void* data, GLsizei size) const {
    Bind();
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
    Unbind();
}
