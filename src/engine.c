#include "engine.h"

windowData *createWindow() {
    windowData *result = malloc(sizeof(windowData));

    SDL_Init(SDL_INIT_VIDEO);

    result->window = SDL_CreateWindow(
        "Run Dachshund!", 
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT,
        SDL_WINDOW_SHOWN);
    
    result->renderer = SDL_CreateRenderer(result->window, -1, SDL_RENDERER_ACCELERATED);

    return result;
}

void gameLoop() {
    int         quit = 0;
    SDL_Event   event;

    windowData  *window = createWindow();
    gameData    state;

    
    

    while (!quit) {
        while(SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = 1;
            }
        }
        
    }
}