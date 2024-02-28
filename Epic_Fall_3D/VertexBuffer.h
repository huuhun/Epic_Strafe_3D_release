#pragma once
class VertexBuffer {

public:
	VertexBuffer();
	~VertexBuffer();

	void Bind() const;
	void Unbind() const;

	void BufferData(const void* data, const GLuint& dataTypeSize) const;

	unsigned int m_ID;
};