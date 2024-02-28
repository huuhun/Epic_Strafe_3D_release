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
#include "IndexBuffer.h"
#include "Texture.h"

int main(int argc, char* args[]) {

    if (!Window::initSDL()) return -1;
    SDL_Window* window{ Window::createGLWindow("Epic Fall 3D", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WindowSettings::SCREEN_WIDTH, WindowSettings::SCREEN_HEIGHT, SDL_WINDOW_SHOWN) };
    SDL_GLContext context{ Window::createGLContext(window)};
    Window::loadGLFunctionPointers();
    Window::setGLVersion(4);
    Window::getGLVersion();

    // configure global opengl state
    //glEnable(GL_DEPTH_TEST); //this cause the 2D triangle can't be drawn

    //Texture texture1("res/textures/brick-wall.jpg");

    // Set up vertex data
    float vertices[] = {
        // positions          // colors           // texture coords
         0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
         0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
    };

    unsigned int indices[] = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };

    // Generate vao, vbo, ebo
    VertexArray vao;
    VertexBuffer vbo;
    IndexBuffer ebo;

    vao.Bind();

    vbo.Bind();
    vbo.BufferData(vertices, sizeof(vertices) / sizeof(vertices[0]));

    // position attribute
    VertexArray::LinkAttrib(0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);

    // color attribute
    VertexArray::LinkAttrib(1, 3, GL_FLOAT, 8 * sizeof(float), (void*)( 3 * sizeof(float) ));
    
    // texture coord attribute
    VertexArray::LinkAttrib(2, 2, GL_FLOAT, 8 * sizeof(float), (void*)( 6 * sizeof(float) ));

    ebo.Bind();
    ebo.BufferData(indices, sizeof(indices)/sizeof(indices[0]));

    // Unbind the VAO and VBO
    vbo.Unbind();
    vao.Unbind();

    enableGLDebugContext();

    // tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
    Shader shader("res/shaders/shader460.vert", "res/shaders/shader460.frag");
    shader.Use();

    Texture brickWallBlockTexture("res/textures/brick-wall.jpg");

    //shader.setInt("texture1", 0);
    // Main rendering loop
    Renderer renderer;
    renderer.setClearColor();
    SDL_Event event;
    while( true ) {
        while( SDL_PollEvent(&event) ) {
            if( event.type == SDL_QUIT )
                goto cleanup;
        }        
        //Render here
        renderer.Clear();
        // bind textures on corresponding texture units
        brickWallBlockTexture.Bind();
       /* glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1.getID());*/

        shader.Use();
        vao.Bind();
        //renderer.DrawElements();
        renderer.DrawElements(sizeof(indices)/sizeof(indices[0])); //6 is the num of indices
        vao.Unbind();

        SDL_GL_SwapWindow(window);
    }

cleanup:
    // Destroy the window and quit SDL
    Window::destroyWindow(context, window);

    return 0;
}
