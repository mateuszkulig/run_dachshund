#include "SDL.h"

#define DEFAULT_WINDOW_WIDTH    800
#define DEFAULT_WINDOW_HEIGHT   600
#define PLAYER_COUNT            2
#define MOVE_SPEED              3

// container for SDL stuff
typedef struct windowData {
    SDL_Window      *window;
    SDL_Renderer    *renderer;
    SDL_Rect        *background;
} windowData;

typedef struct playerData {
    int         top, bottom;
    int         right, left;
    SDL_Rect    *image;
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
void gameLoop();

// init a player
playerData *addPlayer(int t, int b, int r, int l, SDL_Rect *img);

// move a player
void move(playerData *player, int du, int rl);

// control the keys and set according data in moveData
void keyControl(moveData *moves, SDL_Event event);
