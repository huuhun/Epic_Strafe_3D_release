#include <SDL.h>
#include <iostream>
int main(int argc, char* args[]) {
    // Initialize SDL
    if( SDL_Init(SDL_INIT_VIDEO) < 0 ) {
        std::cout << "SDL could not initialize! SDL_Error: %s\n"<< SDL_GetError()<<"\n";
        return -1;
    }

    // Create a window
    SDL_Window* window = SDL_CreateWindow("SDL Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);
    if( window == NULL ) {
        std::cout << "Window could not be created! SDL_Error: %s\n"<< SDL_GetError()<<"\n";
        return -1;
    }

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
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}