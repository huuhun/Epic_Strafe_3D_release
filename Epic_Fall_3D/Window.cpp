#include <iostream>
#include <glad/glad.h>
#include "Window.h"

bool Window::initGLFW()
{
	// Initialize SDL
	if( !glfwInit() ) {
		std::cerr << "glfw could not initialize! SDL_Error: " << glfwGetError(nullptr) << "\n";
		return false;
	}

	return true;
}

bool Window::initSDL_TTF()
{
	if( TTF_Init() < 0 ) {
		std::cerr << "Failed to init SDL_ttf: " << TTF_GetError() << "\n";
		glfwTerminate();
		return -1;
	}
}

GLFWwindow* Window::createGLWindow(const std::string& windowName, const int& w, const int& h)
{
	// WARNING: comment this line in a release build! 
	//SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG);

	// Create a window
	GLFWwindow* window = glfwCreateWindow(w, h, windowName.c_str(), NULL, NULL);
	if( !window ) {
		std::cerr << "Window could not be created! SDL_Error: %s\n" << glfwGetError(nullptr) << "\n";
		//glfwTerminate();
	}

	return window;
}

void Window::createGLContext(GLFWwindow* window) {

	glfwMakeContextCurrent(window);
}

bool Window::loadGLFunctionPointers()
{
	if( !gladLoadGLLoader((GLADloadproc)glfwGetProcAddress) ) {
		std::cerr << "Failed to initialize GLAD" << std::endl;
		return false;
	}
	return true;
}

void Window::setGLVersion(const int& version)
{
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, version);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


#ifdef __APPLE__
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);
#endif
}

void Window::setGLGlobalState(GLFWwindow* window)
{
	glEnable(GL_DEPTH_TEST); // REMOVE THIS IF DRAW 2D ONLY
	// tell GLFW to capture our mouse
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); //disable mouse here
}

void Window::getGLVersion() {
	const GLubyte* version = glGetString(GL_VERSION);

	if( version )
		std::cout << "OpenGL Version: " << version << std::endl;
	else
		std::cerr << "Failed to retrieve OpenGL version information." << std::endl;

}

void Window::closeSDL(TTF_Font* font) {
	TTF_CloseFont(font);
	if( font != nullptr )
	{
		font = nullptr;
	}
	TTF_Quit();
}

void Window::destroyWindow()
{
	glfwTerminate();
}
