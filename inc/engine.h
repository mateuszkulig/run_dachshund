#include "SDL.h"

#define DEFAULT_WINDOW_WIDTH    800
#define DEFAULT_WINDOW_HEIGHT   600

// container for SDL stuff
typedef struct windowData {
    SDL_Window      *window;
    SDL_Renderer    *renderer;
} windowData;

typedef struct playerData {
    int         x;
    int         y;
    int         top, bottom;
    int         right, left;
    SDL_Rect    *image;
} playerData;

typedef struct gameData {
    playerData  *players[1];
} gameData;

// create the window and renderer
windowData *createWindow();

// main game loop
void gameLoop();

