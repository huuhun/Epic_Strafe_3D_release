#pragma once
#include <glfw3.h>
#include <SDL_ttf.h>
class Window
{
public:
	static bool initGLFW();
	static bool initSDL_TTF();
	static GLFWwindow* createGLWindow(const std::string& windowName, const int& w, const int& h);
	static void createGLContext(GLFWwindow* window);
	static bool loadGLFunctionPointers();
	static void setGLVersion(const int& version);
	static void setGLGlobalState(GLFWwindow* window);

	// Get OpenGL version information
	static void getGLVersion();

	static void destroyWindow();

private:

};
