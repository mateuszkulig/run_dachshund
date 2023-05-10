#include "engine.h"
#include "encoder_decoder.h"

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

void move(playerData *player, int du, int rl) {
    player->bottom += du;
    player->top += du;
    player->left += rl;
    player->right += rl;

    player->image->x += rl;
    player->image->y += du;
    
}

void keyControl(moveData *moves, SDL_Event event) {
    // ifs instead of else if are intentional 
    if (event.type == SDL_KEYDOWN && event.key.keysym.scancode == SDL_SCANCODE_LEFT) {    
        moves->l = 1;
    }
    if (event.type == SDL_KEYUP && event.key.keysym.scancode == SDL_SCANCODE_LEFT) {    
        moves->l = 0;
    }

    if (event.type == SDL_KEYDOWN && event.key.keysym.scancode == SDL_SCANCODE_RIGHT) {    
        moves->r = 1;
    }
    if (event.type == SDL_KEYUP && event.key.keysym.scancode == SDL_SCANCODE_RIGHT) {    
        moves->r = 0;
    }

    if (event.type == SDL_KEYDOWN && event.key.keysym.scancode == SDL_SCANCODE_UP) {    
        moves->u = 1;
    }
    if (event.type == SDL_KEYUP && event.key.keysym.scancode == SDL_SCANCODE_UP) {    
        moves->u = 0;
    }

    if (event.type == SDL_KEYDOWN && event.key.keysym.scancode == SDL_SCANCODE_DOWN) {    
        moves->d = 1;
    }
    if (event.type == SDL_KEYUP && event.key.keysym.scancode == SDL_SCANCODE_DOWN) {    
        moves->d = 0;
    }
}

void gameLoop(int playerNumber) {
    int         quit = 0;
    SDL_Event   event;
    unsigned int lastTicks = SDL_GetTicks();
    unsigned int currentTicks = SDL_GetTicks();

    windowData  *window = createWindow();
    gameData    state;
    moveData    moves;
    playerData  *currentPlayer;

    moves.d = 0;
    moves.u = 0;
    moves.r = 0;
    moves.l = 0;

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
    
    currentPlayer = state.players[playerNumber];
    int socketCycle = playerNumber ? 1 : 0;


    while (!quit) {
        while(SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = 1;
                break;
            }
            keyControl(&moves, event);
        }

        // framerate limit
        currentTicks = SDL_GetTicks();
        if (currentTicks - lastTicks > 1000/60) {
            lastTicks = currentTicks;
        } else {
            continue;
        }

        move(currentPlayer, (-moves.u + moves.d) * MOVE_SPEED, (-moves.l + moves.r) * MOVE_SPEED);

        // draw background
        SDL_SetRenderDrawColor(window->renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderFillRect(window->renderer, window->background);

        // draw players
        SDL_SetRenderDrawColor(window->renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
        for (size_t i=0; i<PLAYER_COUNT; ++i) {
            SDL_RenderFillRect(window->renderer, state.players[i]->image);
        }

        SDL_RenderPresent(window->renderer);
    }
    
}