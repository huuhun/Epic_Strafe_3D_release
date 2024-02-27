#include <glad/glad.h>
#include "Debugger.h"
#include "VertexBuffer.h"

VertexBuffer::VertexBuffer() 
	: m_ID(0)
{
	GLCall(glGenBuffers(1, &m_ID));
}

VertexBuffer::~VertexBuffer()
{
	GLCall(glDeleteBuffers(1, &m_ID));
}

void VertexBuffer::Bind() const
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_ID));
}

void VertexBuffer::Unbind() const
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

// Fill the VBO with data
void VertexBuffer::BufferData(const void* data, GLsizei size) const {
    Bind();
	GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
    Unbind();
}
