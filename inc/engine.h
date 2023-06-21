#include "SDL.h"
#include "client.h"
#include "server.h"
#include "time.h"

#pragma once 
#define DEFAULT_WINDOW_WIDTH    800
#define DEFAULT_WINDOW_HEIGHT   600
#define PLAYER_COUNT            2
#define MOVE_SPEED              3
#define PLAYER_ANIMATIONS       4
#define ANIMATION_SLOWDOWN      8
#define TOP_COVER_HEIGHT        150
#define SCROLLING_SPEED         2
#define SHOT_SPEED              4
#define TREE_SPEED              1

// container for SDL stuff
typedef struct windowData {
    SDL_Window      *window;
    SDL_Renderer    *renderer;
    SDL_Rect        *background;
    SDL_Surface     *bg_texture;
    SDL_Rect        *bg_top;
    SDL_Surface     *bg_top_texture;
    SDL_Surface     *surface;
} windowData;

typedef struct playerData {
    int         top, bottom;
    int         right, left;
    SDL_Rect    *image;
    SDL_Surface **texture;
    int         animCount;
} playerData;

typedef struct gameData {
    playerData  *players[PLAYER_COUNT];
    playerData  *shots[PLAYER_COUNT];
    playerData  *tree;
    int         shotStatus[PLAYER_COUNT];
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
playerData *addPlayer(int t, int l, int b, int r, SDL_Rect *img);

// move a player
void move(playerData *player, int du, int rl);

// move a shot
void shotControl(playerData *shot, int *shotStatus);

// control the keys and set according data in moveData
void keyControl(moveData *moves, playerData *shot, playerData *player, int *shotStatus, SDL_Event event, int *overload);

// move the tree
void treeControl(playerData *tree);

// add surface from file to player structure
void addPlayerAnimation(windowData *window, playerData *player, char *filename);

// handle the collision between objects
void handleCollision(playerData **players, playerData **shots, playerData *tree, int *shotStatus);
