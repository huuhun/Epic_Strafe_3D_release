#pragma once
class IndexBuffer {

private:
	unsigned int m_ID;
public:
	IndexBuffer();
	~IndexBuffer();

	void Bind() const;
	void Unbind() const;
	void BufferData(const void* data) const;
};