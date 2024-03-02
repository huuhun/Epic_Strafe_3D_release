#pragma once
#include <glfw3.h>
class Window
{
public:
	static bool initGLFW();
	static GLFWwindow* createGLWindow(const std::string& windowName, const int& w, const int& h);
	static void createGLContext(GLFWwindow* window);
	static bool loadGLFunctionPointers();
	static void setGLVersion(const int& version);

	// Get OpenGL version information
	static void getGLVersion();

	static void destroyWindow();

private:

};
