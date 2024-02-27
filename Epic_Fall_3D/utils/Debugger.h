#pragma once
#include <glad/glad.h>

//#define ASSERT(x) if (!(x)) __debugbreak(); // MSVC only
//#define GLCall(x) GLClearError(); \
//                    x; \
//                    ASSERT(GLLogCall(#x, __FILE__, __LINE__))

void GLAPIENTRY glDebugOutput(GLenum source, GLenum type, unsigned int id, GLenum severity,
    GLsizei length, const char* message, const void* userParam);

void enableGLDebugContext();
