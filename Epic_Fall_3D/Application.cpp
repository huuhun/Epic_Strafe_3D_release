#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <SDL.h>
#include <glad/glad.h>

#include "Window.h"

int main(int argc, char* args[]) {

	if( !Window::initSDL() ) return -1;

	SDL_Window* window{ Window::createGLWindow
	("Epic Fall 3D", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600)};

	SDL_GLContext glContext{ Window::createGLContext(window) };
	if ( !Window::loadGLFunctionPointers()) return -1;
	Window::setGLVersion(3);

	// configure global opengl state
	// -----------------------------
	glEnable(GL_DEPTH_TEST);

	// Run the event loop
	bool quit = false;
	SDL_Event e;
	while( !quit ) {
		while( SDL_PollEvent(&e) != 0 ) {
			if( e.type == SDL_QUIT ) {
				quit = true;
			}
		}
		// Render here

		// Update the screen
		SDL_GL_SwapWindow(window);
	}

	// Destroy window and quit SDL
	Window::destroyWindow(glContext, window);

	return 0;
}
