#include <iostream>
#include "VertexArray.h"
VertexArray::VertexArray()
{
   glGenVertexArrays(1, &m_ID);
}

VertexArray::~VertexArray()
{
    glDeleteVertexArrays(1, &m_ID);
    std::cout << "VAO deleted\n";
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
void VertexArray::LinkAttrib(GLuint layout, GLint numComponents, GLenum type, GLsizei stride, const void* offset){

    glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);
    glEnableVertexAttribArray(layout);
}

// Delete the VertexArray
void VertexArray::Delete() const {
    glDeleteVertexArrays(1, &m_ID);
}
