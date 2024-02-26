#pragma once
#include <SDL.h>
class Window
{
public:
	static bool initSDL();
	static SDL_Window* createWindow();
	static SDL_GLContext createGLContext(SDL_Window*& window);
	static bool loadGLFunctionPointers();
	static void setGLVersion();

private:

};
