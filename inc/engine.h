#include "SDL.h"

#define DEFAULT_WINDOW_WIDTH    800
#define DEFAULT_WINDOW_HEIGHT   600

// container for SDL stuff
typedef struct windowData {
    SDL_Window      *window;
    SDL_Renderer    *renderer;
} windowData;

// create the window and renderer
windowData *createWindow();