#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>

const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;

// graph settings
const float SCALE = 50.0f;  // 30 pixels = 1 unit

// application state
typedef struct {
    SDL_Window *window;
    SDL_Renderer *renderer;
    bool quit;

    int screen_width;
    int screen_height;
    int center_x;
    int center_y;
} AppContext;

bool init_app(AppContext *app);
void process_input(AppContext *app);
void cleanup_app(AppContext *app);
void render_app(AppContext *app);
bool print_sdl_error(const char *message);
void draw_axes(AppContext *app);
void draw_grid(AppContext *app);

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
    if (SDL_Init(SDL_INIT_VIDEO) < 0) return print_sdl_error("SDL initialization failed");

    app->window = SDL_CreateWindow(
        "grphx calculator",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        SCREEN_WIDTH,
        SCREEN_HEIGHT,
        SDL_WINDOW_RESIZABLE
    );
    if (!app->window) return print_sdl_error("Window failed to create");

    app->renderer = SDL_CreateRenderer(
        app->window,
        -1,
        SDL_RENDERER_ACCELERATED
    );
    if (!app->renderer) return print_sdl_error("Renderer failed to create");

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
    SDL_GetWindowSize(app->window, &app->screen_width, &app->screen_height);
    app->center_x = app->screen_width / 2;
    app->center_y = app->screen_height / 2;

    SDL_SetRenderDrawColor(app->renderer, 44, 0, 30, 255); // 62, 32, 83 // 94, 39, 80
    SDL_RenderClear(app->renderer);

    draw_grid(app);
    draw_axes(app);
    // draw_graph(app);

    SDL_RenderPresent(app->renderer);
}

void cleanup_app(AppContext *app) {
    if (app->renderer) SDL_DestroyRenderer(app->renderer);
    if (app->window) SDL_DestroyWindow(app->window);
    SDL_Quit();
}

// helper function to print SDL errors
bool print_sdl_error(const char *message) {
    printf("ERROR: %s: %s\n", message, SDL_GetError());
    return false;
}


void draw_grid(AppContext *app) {    
    SDL_SetRenderDrawColor(app->renderer, 60, 60, 60, 255);

    int scale_int = (int)SCALE; // pixel coordinates are integers

    int offset_x = app->center_x % scale_int;

    // vertikal lines
    for (int x = offset_x; x < app->screen_width; x += scale_int) {
        SDL_RenderDrawLine(app->renderer, x, 0, x, app->screen_height);
    }

    int offset_y = app->center_y % scale_int;

    // horizontal lines
    for (int y = offset_y; y < app->screen_height; y += scale_int) {
        SDL_RenderDrawLine(app->renderer, 0, y, app->screen_width, y);
    }

}

void draw_axes(AppContext *app) {
    SDL_SetRenderDrawColor(app->renderer, 255, 255, 255, 255);
    SDL_RenderDrawLine(app->renderer, 0, app->center_y, app->screen_width, app->center_y);
    SDL_RenderDrawLine(app->renderer, app->center_x, 0, app->center_x, app->screen_height);
}