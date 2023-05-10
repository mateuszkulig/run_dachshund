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

    result->background = malloc(sizeof(SDL_Rect));
    result->background->x = 0;
    result->background->y = 0;
    result->background->w = DEFAULT_WINDOW_WIDTH;
    result->background->h = DEFAULT_WINDOW_HEIGHT;

    return result;
}

playerData *addPlayer(int t, int l, int b, int r, SDL_Rect *img) {
    playerData *player = malloc(sizeof(playerData));
    player->top = t;
    player->bottom = b;
    player->right = r;
    player->left = l;
    player->image = img;
    
    return player;
}

void gameLoop() {
    int         quit = 0;
    SDL_Event   event;

    windowData  *window = createWindow();
    gameData    state;

    SDL_Rect    rectP1, rectP2;

    rectP1.x = 200;
    rectP1.y = 400;
    rectP1.w = 100;
    rectP1.h = 100;

    rectP2.x = 500;
    rectP2.y = 400;
    rectP2.w = 100;
    rectP2.h = 100;

    state.players[0] = addPlayer(200, 400, 100, 200, &rectP1);
    state.players[1] = addPlayer(500, 400, 100, 600, &rectP2);
    

    while (!quit) {
        while(SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = 1;
            }
        }
        
        // draw background
        SDL_SetRenderDrawColor(window->renderer, 0, 0, 255, SDL_ALPHA_OPAQUE);
        SDL_RenderFillRect(window->renderer, window->background);

        // draw players
        SDL_SetRenderDrawColor(window->renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
        for (size_t i=0; i<PLAYER_COUNT; ++i) {
            SDL_RenderFillRect(window->renderer, state.players[i]->image);
        }

        SDL_RenderPresent(window->renderer);
    }
}