#include "VertexArray.h"

VertexArray::VertexArray() {
    glGenVertexArrays(1, &m_ID);
}

// Bind the VertexArray
void VertexArray::Bind() const {
    glBindVertexArray(m_ID);
}

// Unbind the VertexArray
void VertexArray::Unbind() const {
    glBindVertexArray(0);
}

// Link a VBO to the VertexArray and set the vertex attribute pointers
void VertexArray::LinkAttrib(const VertexBuffer& vbo, GLuint layout, GLuint numComponents, GLenum type, GLsizei stride, const void* offset) const {
    Bind();
    vbo.Bind();
    glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);
    glEnableVertexAttribArray(layout);
    vbo.Unbind();
    Unbind();
}

// Delete the VertexArray
void VertexArray::Delete() const {
    glDeleteVertexArrays(1, &m_ID);
}
