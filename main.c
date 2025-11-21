#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>

const int SCREEN_WIDTH = 1200;
const int SCREEN_HEIGHT = 780;

bool quit = false;

int main(void) {
    SDL_Event event;
    SDL_Init(SDL_INIT_VIDEO);
    
    SDL_Window *window;
    window = SDL_CreateWindow(
        "grphx calculator",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        SCREEN_WIDTH,
        SCREEN_HEIGHT,
        0
    );

    while(!quit) {
        SDL_WaitEvent(&event);
        switch (event.type) {
        case SDL_QUIT:
            quit = true;
            break;
        }
    }
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
