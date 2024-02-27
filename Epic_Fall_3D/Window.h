#pragma once
#include <SDL.h>
class Window
{
public:
	static bool initSDL();
	static SDL_Window* createGLWindow(const std::string& windowName, const int& x, const int& y, const int& w, const int& h, const Uint32& flag);
	static SDL_GLContext createGLContext(SDL_Window* window);
	static bool loadGLFunctionPointers();
	static void setGLVersion(const int& version);

	// Get OpenGL version information
	static void getGLVersion();

	static void destroyWindow(SDL_GLContext& glContext, SDL_Window*& window);

private:

};
