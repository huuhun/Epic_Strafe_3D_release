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

    // configure global opengl state
    //glEnable(GL_DEPTH_TEST); //this cause the 2D triangle can't be drawn

    // Set up vertex data
    float vertices[] = {
        // positions          // colors           // texture coords
         0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
         0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
    };

    unsigned indices[] = {
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

    //Texture brickWallBlockTexture("res/textures/brick-wall.png");
    unsigned int texture1, texture2;
    std::string path{ "res/textures/brick-wall.png" };
    // texture 1
    // ---------
    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1);
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
    // The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
    unsigned char* data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
    if( data )
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

    //Texture faceTexture("res/textures/face.png");
    path = "res/textures/face.png";
    glGenTextures(1, &texture2);
    glBindTexture(GL_TEXTURE_2D, texture2);
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
    if( data )
    {
        // note that the awesomeface.png has transparency and thus an alpha channel, so make sure to tell OpenGL the data type is of GL_RGBA
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);


    // tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
    shader.Use();// don't forget to activate/use the shader before setting uniforms!
    //shader.setInt("brickWallBlockTexture", 0);
    //shader.setInt("faceTexture", 1);
    glUniform1i(glGetUniformLocation(shader.getID(), "texture1"), 0);
    glUniform1i(glGetUniformLocation(shader.getID(), "texture2"), 1);
    std::cout << shader.getID() << "\n";
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
       // brickWallBlockTexture.Bind();
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);
        //std::cout << brickWallBlockTexture.getID() << "\n";
            
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
