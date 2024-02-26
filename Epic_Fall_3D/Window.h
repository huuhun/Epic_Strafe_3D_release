#pragma once
#include <SDL.h>
class Window
{
public:
	static bool initSDL();
	static SDL_Window* createGLWindow(const std::string& windowName, const int& x, const int& y, const int& w, const int& h);
	static SDL_GLContext createGLContext(SDL_Window*& window);
	static bool loadGLFunctionPointers();
	static void setGLVersion(const int& version);
	static void destroyWindow(SDL_GLContext& glContext, SDL_Window*& window);

private:

};
