#include "SDL.h"
#include "client.h"
#include "server.h"
#pragma once 
#define DEFAULT_WINDOW_WIDTH    800
#define DEFAULT_WINDOW_HEIGHT   600
#define PLAYER_COUNT            2
#define MOVE_SPEED              3

// container for SDL stuff
typedef struct windowData {
    SDL_Window      *window;
    SDL_Renderer    *renderer;
    SDL_Rect        *background;
    SDL_Surface     *surface;
} windowData;

typedef struct playerData {
    int         top, bottom;
    int         right, left;
    SDL_Rect    *image;
    SDL_Surface *texture;
} playerData;

typedef struct gameData {
    playerData  *players[PLAYER_COUNT];
} gameData;

typedef struct moveData {
    int u;
    int d;
    int l;
    int r;
} moveData;

// create the window and renderer
windowData *createWindow();

// main game loop
void gameLoop(int playerNumber);

// init a player
playerData *addPlayer(int t, int l, int b, int r, SDL_Rect *img, SDL_Surface *texture);

// move a player
void move(playerData *player, int du, int rl);

// control the keys and set according data in moveData
void keyControl(moveData *moves, SDL_Event event);
