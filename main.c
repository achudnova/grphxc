#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>

const int SCREEN_WIDTH = 1200;
const int SCREEN_HEIGHT = 780;

// application state
typedef struct {
    SDL_Window *window;
    SDL_Renderer *renderer;
    bool quit;
} AppContext;

bool init_app(AppContext *app);
void process_input(AppContext *app);
void cleanup_app(AppContext *app);
void render_app(AppContext *app);
void print_sdl_error(const char *message);

int main(void) {
    AppContext app;

    if (!init_app(&app)) return 1;

    while (!app.quit) {
        process_input(&app);
        render_app(&app);
        SDL_Delay(16); // cap framerate to save cpu
    }

    cleanup_app(&app);

    return 0;
}

bool init_app(AppContext *app) {
    app->quit = false;

    // initialize SDL video subsystem
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("ERROR: SDL initialization failed: %s\n", SDL_GetError());
        return false;
    }

    app->window = SDL_CreateWindow(
        "grphx calculator",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        SCREEN_WIDTH,
        SCREEN_HEIGHT,
        0
    );
    if (!app->window) {
        printf("ERROR: Window failed to create; %s\n", SDL_GetError());
        return false;
    }

    app->renderer = SDL_CreateRenderer(
        app->window,
        -1,
        SDL_RENDERER_ACCELERATED
    );
    if (!app->renderer) {
        printf("ERROR: Renderer failed to create: %s\n", SDL_GetError());
        return false;
    }

    return true;
}

void process_input(AppContext *app) {
    SDL_Event event;

    while(SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_QUIT:
            app->quit = true;
            break;
        }
    }
}

void render_app(AppContext *app) {
    SDL_SetRenderDrawColor(app->renderer, 44, 0, 30, 255); // 62, 32, 83 // 94, 39, 80
    SDL_RenderClear(app->renderer);
    SDL_RenderPresent(app->renderer);
}

void cleanup_app(AppContext *app) {
    if (app->renderer) SDL_DestroyRenderer(app->renderer);
    if (app->window) SDL_DestroyWindow(app->window);
    SDL_Quit();
}