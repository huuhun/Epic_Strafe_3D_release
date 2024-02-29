#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <SDL.h>
#include <glad/glad.h>
#include <stb_image/stb_image.h>

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


    float vertices[] = {
    
         0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, 
         0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, 
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, 
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  
    };

    unsigned indices[] = {
        0, 1, 3, 
        1, 2, 3  
    };

    VertexArray vao;
    VertexBuffer vbo;
    IndexBuffer ebo;

    vao.Bind();

    vbo.Bind();
    vbo.BufferData(vertices, sizeof(vertices) / sizeof(vertices[0]));

    VertexArray::LinkAttrib(0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);

    VertexArray::LinkAttrib(1, 3, GL_FLOAT, 8 * sizeof(float), (void*)( 3 * sizeof(float) ));
    
    VertexArray::LinkAttrib(2, 2, GL_FLOAT, 8 * sizeof(float), (void*)( 6 * sizeof(float) ));

    ebo.Bind();
    ebo.BufferData(indices, sizeof(indices)/sizeof(indices[0]));

    vbo.Unbind();
    vao.Unbind();

    enableGLDebugContext();

    Shader shader("res/shaders/shader460.vert", "res/shaders/shader460.frag");

    Texture brickWallTexture("res/textures/brick-wall.png");
    Texture faceTexture("res/textures/face.png");

    shader.Use();
    
    shader.setInt("brickWallTexture", 0);
    shader.setInt("faceTexture", 1);

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
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, brickWallTexture.getID());
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, faceTexture.getID());
            
        shader.Use();
        vao.Bind();
        //renderer.DrawElements();
        renderer.DrawElements(sizeof(indices)/sizeof(indices[0])); // pass in the num of indices
        vao.Unbind();

        SDL_GL_SwapWindow(window);
    }

cleanup:
    Window::destroyWindow(context, window);

    return 0;
}
