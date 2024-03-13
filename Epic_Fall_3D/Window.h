#pragma once
#include <glfw3.h>
#include <ft2build.h>
#include FT_FREETYPE_H
class Window
{
public:
	static bool initGLFW();
	static void initFreeType(const std::string& path, FT_Library& ft, FT_Face& face);
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
