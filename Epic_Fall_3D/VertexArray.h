#pragma once

#include <glad/glad.h>

class VertexArray {
public:
    VertexArray();

    ~VertexArray();

    // Bind the VAO
    void Bind() const;

    // Unbind the VAO
    void Unbind() const;

    // Link a VBO to the VAO and set the vertex attribute pointers
    static void LinkAttrib( GLuint layout, GLint numComponents, GLenum type, GLsizei stride, const void* offset);

    // Delete the VAO
    void Delete() const;

private:
    GLuint m_ID;
};

