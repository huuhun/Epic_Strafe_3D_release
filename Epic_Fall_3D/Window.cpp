#include <iostream>
#include <glad/glad.h>
#include "Window.h"

bool Window::initSDL()
{
	// Initialize SDL
	if( SDL_Init(SDL_INIT_VIDEO) < 0 ) {
		std::cerr << "SDL could not initialize! SDL_Error: %s\n" << SDL_GetError() << "\n";
		return false;
	}

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	return true;
}

SDL_Window* Window::createGLWindow(const std::string& windowName, const int& x, const int& y, const int& w, const int& h)
{
	// Create a window
	SDL_Window* window = SDL_CreateWindow("SDL Window", x, y, w, h, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
	if( !window ) {
		std::cerr << "Window could not be created! SDL_Error: %s\n" << SDL_GetError() << "\n";
	}

	return window;
}

SDL_GLContext Window::createGLContext(SDL_Window*& window) {

	SDL_GLContext glContext = SDL_GL_CreateContext(window);
	if( !glContext ) {
		std::cerr << "Cannot create context! SDL_Error: %s\n" << SDL_GetError() << "\n";
	}
	return glContext;
}

bool Window::loadGLFunctionPointers()
{
	if( !gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress) ) {
		std::cerr << "Failed to initialize GLAD" << std::endl;
		std::cout << "SDL_GL_GetProcAddress: " << SDL_GL_GetProcAddress << std::endl;
		return false;
	}
	return true;
}

void Window::setGLVersion(const int& version)
{
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, version);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, version);
}

void Window::destroyWindow(SDL_GLContext& glContext, SDL_Window*& window)
{
	SDL_GL_DeleteContext(glContext);
	SDL_DestroyWindow(window);
	SDL_Quit();
}
