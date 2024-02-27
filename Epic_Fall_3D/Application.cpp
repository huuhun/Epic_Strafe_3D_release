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

int main(int argc, char* args[]) {

    if (!Window::initSDL()) return -1;
    SDL_Window* window{ Window::createGLWindow("Epic Fall 3D", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WindowSettings::SCREEN_WIDTH, WindowSettings::SCREEN_HEIGHT, SDL_WINDOW_SHOWN) };
    SDL_GLContext context{ Window::createGLContext(window)};
    Window::loadGLFunctionPointers();
    Window::setGLVersion(4);

    // configure global opengl state
    //glEnable(GL_DEPTH_TEST); //this cause the 2D triangle can't be drawn

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
    vao.Bind();

    // Bind the VBO and set the vertex data
    vbo.Bind();
    vbo.BufferData(sizeof(vertices), vertices);

    // Set the vertex attribute pointers
    vao.LinkAttrib(0, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);

    // Unbind the VAO and VBO
    vbo.Unbind();
    vao.Unbind();

    //Enable errors checker
    enableGLDebugContext();

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

        //Render here
        renderer.Clear();
        shader.Use();
        vao.Bind();
        renderer.Draw();
        vao.Unbind();

        // Swap buffers
        SDL_GL_SwapWindow(window);
    }

cleanup:
    // Destroy the window and quit SDL
    Window::destroyWindow(context, window);

    return 0;
}
