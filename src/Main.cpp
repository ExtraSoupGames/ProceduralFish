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

    SDL_version compiled;
    SDL_version linked;

    SDL_VERSION(&compiled);
    SDL_GetVersion(&linked);
    SDL_Log("We compiled against SDL version %u.%u.%u ...\n",
        compiled.major, compiled.minor, compiled.patch);
    SDL_Log("But we are linking against SDL version %u.%u.%u.\n",
        linked.major, linked.minor, linked.patch);

    SDL_Event event;

    SDL_Window* window = SDL_CreateWindow(
        "Multiplayer ship game client",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        800, 600,
        SDL_WINDOW_SHOWN
    );
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    bool is_running = true;
    SDL_Color fishColour = *new SDL_Color{0, 255, 255};
    Animatable* fishTest = new Animatable(
        *new vector<int>{ 5, 10, 20, 40, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30,30, 30,30, 30, 30,  30, 30, 20, 10 });
    fishTest->GetElementAt(3)->AddDetail(0.5 * M_PI, 10, 5, SDL_Color{255, 0, 0, 255});
    fishTest->GetElementAt(3)->AddDetail(1.5 * M_PI, 10, 5, SDL_Color{ 255, 0, 0, 255 });
#pragma endregion initialization
#pragma region mainLoop

    Uint64 currentTime = SDL_GetPerformanceCounter();
    Uint64 lastFrameTime = 0;
    double deltaTime = 0;
    while (is_running) {
        fishTest->Update();
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        fishTest->Render(renderer);
        SDL_RenderPresent(renderer);
#pragma region input
        while (SDL_PollEvent(&event)) {
            int* mouseX = new int(5);
            int* mouseY = new int(5);
            SDL_GetMouseState(mouseX, mouseY);
            fishTest->MoveTo(*mouseX, *mouseY);
            if ((event.type == SDL_KEYDOWN || event.type == SDL_KEYUP) && event.key.repeat == 0) {
                switch (event.key.keysym.sym) {
                case SDLK_ESCAPE:
                    is_running = false;
                    break;
                case SDLK_p:
                    cout << "P PRESSED" << endl;
                    break;
                default:
                    break;
                }
            }

            if (event.type == SDL_QUIT) {
                is_running = false;
            }
        }
#pragma endregion input
    }
#pragma endregion mainLoop


    // Clean up
    SDL_Quit();

    return 0;
}