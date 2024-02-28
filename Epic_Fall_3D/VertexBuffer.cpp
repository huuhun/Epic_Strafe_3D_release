#include <iostream>
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
	std::cout << "VBO deleted\n";
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
void VertexBuffer::BufferData(const void* data, const GLuint& numElements) const {
    //Bind();
	glBufferData(GL_ARRAY_BUFFER, numElements * sizeof(data), data, GL_STATIC_DRAW);
	std::cout << data << " sizeof(vertices): " << numElements * sizeof(data) << " " << sizeof(data) << "\n";
    //Unbind();
}
