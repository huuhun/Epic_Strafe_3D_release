#include "VertexArray.h"
#include "Debugger.h"
VertexArray::VertexArray()
    :m_ID(0)
{
    GLCall(glGenVertexArrays(1, &m_ID));
}

VertexArray::~VertexArray()
{
    GLCall(glDeleteVertexArrays(1, &m_ID));
}

// Bind the VertexArray
void VertexArray::Bind() const {
    GLCall(glBindVertexArray(m_ID));
}

// Unbind the VertexArray
void VertexArray::Unbind() const {
    GLCall(glBindVertexArray(0));
}

// Link a VBO to the VertexArray and set the vertex attribute pointers
void VertexArray::LinkAttrib(GLuint layout, GLint numComponents, GLenum type, GLsizei stride, const void* offset) const {

    GLCall(glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset));
    GLCall(glEnableVertexAttribArray(layout));
}

// Delete the VertexArray
void VertexArray::Delete() const {
    GLCall(glDeleteVertexArrays(1, &m_ID));
}
