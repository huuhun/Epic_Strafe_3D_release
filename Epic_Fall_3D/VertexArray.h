#include <glad/glad.h>
#include "VertexBuffer.h"

class VertexBuffer;

class VertexArray {
public:
    VertexArray();

    // Bind the VAO
    void Bind() const;

    // Unbind the VAO
    void Unbind() const;

    // Link a VBO to the VAO and set the vertex attribute pointers
    void LinkAttrib(const VertexBuffer& vbo, GLuint layout, GLuint numComponents, GLenum type, GLsizei stride, const void* offset) const;

    // Delete the VAO
    void Delete() const;

private:
    GLuint m_ID;
};

