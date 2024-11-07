#include <SDL.h>
#include <iostream>
using namespace std;
#include "Animatable.h"
int main(int argc, char* argv[]) {
#pragma region initialization
    // Initialize SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return 1;
    }
    SDL_Event event;

    SDL_Window* window = SDL_CreateWindow(
        "Multiplayer ship game client",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        800, 600,
        SDL_WINDOW_SHOWN
    );
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    bool is_running = true;
#pragma endregion initialization
#pragma region mainLoop

    Uint64 currentTime = SDL_GetPerformanceCounter();
    Uint64 lastFrameTime = 0;
    double deltaTime = 0;
    while (is_running) {
        while (SDL_PollEvent(&event)) {
            if ((event.type == SDL_KEYDOWN || event.type == SDL_KEYUP) && event.key.repeat == 0) {
                switch (event.key.keysym.sym) {
                case SDLK_ESCAPE:
                    is_running = false;
                    break;
                case SDLK_p:
                    cout << "P PRESSED" << endl;
                default:
                    break;
                }
            }

            if (event.type == SDL_QUIT) {
                is_running = false;
            }
        }
    }
#pragma endregion mainLoop


    // Clean up
    SDL_Quit();

    return 0;
}