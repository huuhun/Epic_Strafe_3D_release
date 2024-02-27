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

int main(int argc, char* args[]) {	

	if( !Window::initSDL() ) return -1;

	SDL_Window* window{ Window::createGLWindow
	("Epic Fall 3D", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WindowSettings::SCREEN_WIDTH, WindowSettings::SCREEN_HEIGHT, SDL_WINDOW_SHOWN)};

	SDL_GLContext glContext{ Window::createGLContext(window) };
	if ( !Window::loadGLFunctionPointers()) return -1;
	Window::setGLVersion(4);
	Window::getGLVersion();

	// configure global opengl state
	glEnable(GL_DEPTH_TEST);

	// build and compile our shader program
	Shader gameShader("shaders/shader460.vshader", "shaders/shader460.fshader");

	float vertices[] = {
	   -0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.0f,  0.5f, 0.0f
	};

	// Generate VBO,VAO
	VertexBuffer vbo;
	VertexArray  vao;

	vbo.BufferData(vertices, sizeof(vertices));
	vao.LinkAttrib(vbo, 0, 3, GL_FLOAT, 3 * sizeof(float), nullptr);

	// run the event loop
	bool quit = false;
	SDL_Event e;
	while( !quit ) {
		while( SDL_PollEvent(&e) != 0 ) {
			if( e.type == SDL_QUIT ) 
				quit = true;
			
		}
		// render here
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// update the screen
		SDL_GL_SwapWindow(window);
	}

	// destroy window and quit SDL
	Window::destroyWindow(glContext, window);

	return 0;
}
