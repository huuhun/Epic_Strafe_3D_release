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

	if( !Window::initSDL() ) return -1;

	SDL_Window* window{ Window::createGLWindow
	("Epic Fall 3D", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WindowSettings::SCREEN_WIDTH, WindowSettings::SCREEN_HEIGHT, SDL_WINDOW_SHOWN)};

	SDL_GLContext glContext{ Window::createGLContext(window) };
	if ( !Window::loadGLFunctionPointers()) return -1;
	Window::setGLVersion(4);
	Window::getGLVersion();

	// configure global opengl state
	GLCall(glEnable(GL_DEPTH_TEST));

	// build and compile our shader program
	Shader shader("res/shaders/shader460.vert", "res/shaders/shader460.frag");

	float vertices[] = {
	   -0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.0f,  0.5f, 0.0f
	};

	// Generate VBO,VAO
	VertexBuffer vbo;
	VertexArray  vao;


	vbo.Bind();
	vbo.BufferData(vertices, sizeof(vertices));

	vao.Bind();
	vao.LinkAttrib(0, 3, GL_FLOAT, 3 * sizeof(float), nullptr);

	vbo.Unbind();
	vao.Unbind();

	// run the event loop
	Renderer renderer;
	//renderer.setClearColor();
	bool quit = false;
	SDL_Event e;
	while( !quit ) {
		while( SDL_PollEvent(&e) != 0 ) {
			if( e.type == SDL_QUIT ) 
				quit = true;
		}

		// render here
		// Use the shader program
		renderer.Clear();
		shader.use();
		vao.Bind();
		renderer.Draw(vao);
		vao.Unbind();

		// update the screen
		SDL_GL_SwapWindow(window);
	}

	// destroy window and quit SDL
	Window::destroyWindow(glContext, window);

	return 0;
}
