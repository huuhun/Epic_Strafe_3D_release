#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <SDL.h>
#include <glad/glad.h>

#include "Window.h"
#include "Settings.h"
#include "Shader.h"
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "Renderer.h"
#include "Debugger.h"

//if( !Window::initSDL() ) return -1;
//
//SDL_Window* window{ Window::createGLWindow
//("Epic Fall 3D", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WindowSettings::SCREEN_WIDTH, WindowSettings::SCREEN_HEIGHT, SDL_WINDOW_SHOWN) };
//
//SDL_GLContext glContext{ Window::createGLContext(window) };
//if( !Window::loadGLFunctionPointers() ) return -1;
//Window::setGLVersion(3);
//Window::getGLVersion();
//
//// configure global opengl state
//glEnable(GL_DEPTH_TEST);
//
//// build and compile our shader program
//Shader shader("res/shaders/shader460.vert", "res/shaders/shader460.frag");
//
//float vertices[] = {
//   -0.5f, -0.5f, 0.0f,  // Vertex 1 (bottom-left)
//	0.5f, -0.5f, 0.0f,  // Vertex 2 (bottom-right)
//	0.0f,  0.5f, 0.0f   // Vertex 3 (top)
//};
//
//// Generate VBO,VAO
//VertexBuffer vbo;
//VertexArray  vao;
//
//vao.Bind();
//
//vbo.Bind();
//vbo.BufferData(vertices, sizeof(vertices));
//
//vao.LinkAttrib(0, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);
//
//vbo.Unbind();
//vao.Unbind();
//
//// run the event loop
//Renderer renderer;
//SDL_Event e;
//while( true ) {
//	while( SDL_PollEvent(&e) != 0 ) {
//		if( e.type == SDL_QUIT )
//			goto cleanup;
//	}
//
//	// render here
//	// Use the shader program
//	renderer.setClearColor();
//	renderer.Clear();
//	shader.Use();
//	vao.Bind();
//	renderer.Draw(vao);
//	vao.Unbind();
//
//	// update the screen
//	SDL_GL_SwapWindow(window);
//}
//
//// destroy window and quit SDL
//cleanup:
//Window::destroyWindow(glContext, window);

int main(int argc, char* args[]) {

    // Initialize SDL
    Window::initSDL();
    // Set OpenGL context attributes
    Window::setGLVersion(3);
    // Create an SDL window
    SDL_Window* window{ Window::createGLWindow("Epic Fall 3D", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WindowSettings::SCREEN_WIDTH, WindowSettings::SCREEN_HEIGHT, SDL_WINDOW_SHOWN) };
    // Create an OpenGL context
    SDL_GLContext context{ Window::createGLContext(window)};
    // Load OpenGL functions using GLAD
    Window::loadGLFunctionPointers();

    // Vertex Shader Source
    const char* vertexShaderSource = R"(
        #version 330 core
        layout (location = 0) in vec3 aPos;
        void main() {
            gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
        }
    )";

    // Fragment Shader Source
    const char* fragmentShaderSource = R"(
        #version 330 core
        out vec4 FragColor;
        void main() {
            FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
        }
    )";

    // Compile Vertex Shader, Fragment Shader, link Shaders into a Program
    Shader shader("res/shaders/shader460.vert", "res/shaders/shader460.frag");

    // Set up vertex data
    float vertices[] = {
        -0.5f, -0.5f, 0.0f,  // Vertex 1 (bottom-left)
         0.5f, -0.5f, 0.0f,  // Vertex 2 (bottom-right)
         0.0f,  0.5f, 0.0f   // Vertex 3 (top)
    };

    // Create Vertex Array Object (VAO) and Vertex Buffer Object (VBO)
    VertexArray  vao;
    VertexBuffer vbo;

    // Bind the VAO
    vao.Bind();

    // Bind the VBO and set the vertex data
    vbo.Bind();
    vbo.BufferData(sizeof(vertices), vertices);

    // Set the vertex attribute pointers
    vao.LinkAttrib(0, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);

    // Unbind the VAO and VBO
    vbo.Unbind();
    vao.Unbind();

    // Main rendering loop
    Renderer renderer;
    renderer.setClearColor();
    while( true ) {
        // Process events
        SDL_Event event;
        while( SDL_PollEvent(&event) ) {
            if( event.type == SDL_QUIT )
                goto cleanup;
        }

        // Clear the screen
        renderer.Clear();

        // Use the shader program
        shader.Use();

        // Bind the VAO
        vao.Bind();

        // Draw the triangle
        renderer.Draw(vao);

        // Unbind the VAO
        vao.Unbind();

        // Swap buffers
        SDL_GL_SwapWindow(window);
    }

cleanup:
    // Clean up resources
    
    // Destroy the window and quit SDL
    Window::destroyWindow(context, window);

    return 0;
}
