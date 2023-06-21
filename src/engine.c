#include "engine.h"
#include "encoder_decoder.h"

windowData *createWindow() {
    windowData  *result = malloc(sizeof(windowData));
    SDL_Surface *temp = NULL;

    SDL_Init(SDL_INIT_VIDEO);

    result->window = SDL_CreateWindow(
        "Run Dachshund!", 
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT,
        SDL_WINDOW_SHOWN);
    
    result->renderer = SDL_CreateRenderer(result->window, -1, SDL_RENDERER_SOFTWARE);
    result->surface = SDL_GetWindowSurface(result->window);

    result->background = malloc(sizeof(SDL_Rect));
    result->background->x = 0;
    result->background->y = 0;
    result->background->w = DEFAULT_WINDOW_WIDTH;
    result->background->h = DEFAULT_WINDOW_HEIGHT;

    temp = SDL_LoadBMP("res/bg.bmp");
    result->bg_texture = SDL_ConvertSurfaceFormat(temp, SDL_GetWindowPixelFormat(result->window), 0);
    SDL_FreeSurface(temp);

    result->bg_top = malloc(sizeof(SDL_Rect));
    result->bg_top->x = 0;
    result->bg_top->y = 0;
    result->bg_top->w = DEFAULT_WINDOW_WIDTH;
    result->bg_top->h = TOP_COVER_HEIGHT;

    temp = SDL_LoadBMP("res/bg_up.bmp");
    result->bg_top_texture = SDL_ConvertSurfaceFormat(temp, SDL_GetWindowPixelFormat(result->window), 0);
    SDL_FreeSurface(temp);

    return result;
}

playerData *addPlayer(int t, int l, int b, int r, SDL_Rect *img) {
    playerData *player = malloc(sizeof(playerData));
    player->top = t;
    player->bottom = b;
    player->right = r;
    player->left = l;
    player->image = img;

    player->texture = malloc(sizeof(SDL_Surface *) * PLAYER_ANIMATIONS);
    player->animCount = 0;
    
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

void shotControl(playerData *shot, int *shotStatus) {
    if (shot->top >= DEFAULT_WINDOW_HEIGHT) {
        *shotStatus = 0;
        return;
    }

    shot->bottom += SHOT_SPEED;
    shot->top += SHOT_SPEED;
    shot->image->y += SHOT_SPEED;
}

void keyControl(moveData *moves, playerData *shot, playerData *player, int *shotStatus, SDL_Event event) {
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

    if (event.type == SDL_KEYDOWN && event.key.keysym.scancode == SDL_SCANCODE_SPACE && !(*shotStatus)) {
        shot->top = player->top;
        shot->left = player->left;
        shot->bottom = player->bottom;
        shot->right = player->right;

        shot->image->x = player->image->x + 25; // +25 for being in the middle
        shot->image->y = player->bottom;

        *shotStatus = 1;
    }
}

void addPlayerAnimation(windowData *window, playerData *player, char *filename) {
    SDL_Surface *temp = NULL;
    temp = SDL_LoadBMP(filename);
    player->texture[player->animCount] = SDL_ConvertSurfaceFormat(temp, SDL_PIXELFORMAT_ARGB8888, 0);
    player->animCount++;
    SDL_FreeSurface(temp);
}

void treeControl(playerData *tree) {
    tree->bottom -= TREE_SPEED;
    tree->top -= TREE_SPEED;
    tree->image->y -= TREE_SPEED;
}

void handleCollision(playerData **players, playerData **shots, playerData *tree, int *shotStatus) {
    int x;
    static int count = 0;

    for (size_t i=0; i<PLAYER_COUNT; ++i) {
        if (shotStatus[i] &&(tree->top < shots[i]->bottom && shots[i]->right > tree->left && shots[i]->left < tree->right)) {
                
            count++;
            printf("collision %d\n", count);
            
            shotStatus[i] = !shotStatus[i];

            x = (rand() % (DEFAULT_WINDOW_WIDTH - 50 - 50 + 1)) + 50;  // set new random X; 50 is for lower bound as well -50 for upper one
            tree->left = x;
            tree->right = x + 50;
            tree->image->x = x;

            tree->image->y = DEFAULT_WINDOW_HEIGHT - 50;
            tree->bottom = DEFAULT_WINDOW_HEIGHT;
            tree->top = DEFAULT_WINDOW_HEIGHT - 50;
    }
    }
    
}

void gameLoop(int playerNumber) {
    int         quit = 0;
    SDL_Event   event;
    unsigned int lastTicks = SDL_GetTicks();
    unsigned int currentTicks = SDL_GetTicks();

    windowData  *window = createWindow();
    gameData    state = {0};
    moveData    moves;
    playerData  *currentPlayer = NULL;
    playerData  *otherPlayer = NULL;
    int         currentAnim = 0;

    srand(time(0));

    moves.d = 0;
    moves.u = 0;
    moves.r = 0;
    moves.l = 0;

    SDL_Rect    rectP1, rectP2, rectS1, rectS2, rectT1;
    SDL_Surface *surfP1 = NULL, *surfP2 = NULL, *textureP1 = NULL, *textureP2 = NULL;


    rectP1.x = 200;
    rectP1.y = 100;
    rectP1.w = 100;
    rectP1.h = 100;

    rectP2.x = 500;
    rectP2.y = 100;
    rectP2.w = 100;
    rectP2.h = 100;

    rectS1.x = 1;
    rectS1.y = 1;
    rectS1.w = 50;
    rectS1.h = 50;

    rectS2.x = 1;
    rectS2.y = 1;
    rectS2.w = 50;
    rectS2.h = 50;

    rectT1.x = (DEFAULT_WINDOW_WIDTH / 2) - 25;
    rectT1.y = DEFAULT_WINDOW_HEIGHT - 50;
    rectT1.w = 50;
    rectT1.h = 50;

    state.players[0] = addPlayer(100, 200, 200, 300, &rectP1);
    state.players[1] = addPlayer(100, 500, 200, 600, &rectP2);

    state.shots[0] = addPlayer(1, 1, 51, 51, &rectS1);
    state.shots[1] = addPlayer(1, 1, 51, 51, &rectS2);

    state.tree = addPlayer(DEFAULT_WINDOW_HEIGHT - 50, (DEFAULT_WINDOW_WIDTH / 2) - 25, DEFAULT_WINDOW_HEIGHT, (DEFAULT_WINDOW_WIDTH / 2) + 25, &rectT1);

    addPlayerAnimation(window, state.players[0], "res/jamniczek1_1.bmp");
    addPlayerAnimation(window, state.players[1], "res/jamniczek2_1.bmp");

    addPlayerAnimation(window, state.players[0], "res/jamniczek1_2.bmp");
    addPlayerAnimation(window, state.players[1], "res/jamniczek2_2.bmp");

    addPlayerAnimation(window, state.players[0], "res/jamniczek1_3.bmp");
    addPlayerAnimation(window, state.players[1], "res/jamniczek2_3.bmp");

    addPlayerAnimation(window, state.players[0], "res/jamniczek1_4.bmp");
    addPlayerAnimation(window, state.players[1], "res/jamniczek2_4.bmp");

    addPlayerAnimation(window, state.shots[0], "res/shot.bmp");
    addPlayerAnimation(window, state.shots[1], "res/shot.bmp");

    addPlayerAnimation(window, state.tree, "res/tree.bmp");

    currentPlayer = state.players[playerNumber];
    otherPlayer = state.players[!playerNumber];

    int socketCycle = playerNumber ? 1 : 0;
    platformSocket sock;
    socketCycle ? (sock = clientInit()) : (sock = serverInit());
    char *socketBuffer = NULL;

    while (!quit) {
        // events
        while(SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = 1;
                break;
            }
            keyControl(&moves, state.shots[playerNumber], currentPlayer, &(state.shotStatus[playerNumber]), event);
        }

        // framerate limit
        currentTicks = SDL_GetTicks();
        if (currentTicks - lastTicks > 1000/60) {
            lastTicks = currentTicks;
        } else {
            continue;
        }

        // client-server communication
        if (socketCycle) {
            socketBuffer = encode(currentPlayer, state.shots[playerNumber], state.tree, &(state.shotStatus[playerNumber]));
            sendData(sock, socketBuffer);
            socketCycle = !socketCycle;
        } else {
            socketBuffer = recvData(sock);
            decode(otherPlayer, state.shots[!playerNumber], state.tree, socketBuffer, &(state.shotStatus[!playerNumber]), playerNumber);
            socketCycle = !socketCycle;
        }

        move(currentPlayer, (-moves.u + moves.d) * MOVE_SPEED, (-moves.l + moves.r) * MOVE_SPEED);
        
        if (state.shotStatus[playerNumber]) {
            shotControl(state.shots[playerNumber], &state.shotStatus[playerNumber]);
        }


        
        // only one player controls the tree
        if (playerNumber) {
            treeControl(state.tree);
            handleCollision(state.players, state.shots, state.tree, state.shotStatus);
        } 
        printf("shot status: %d, %d\n", state.shotStatus[0], state.shotStatus[1]);
        

        // draw background
        SDL_BlitSurface(window->bg_texture, NULL, window->surface, window->background);
        if (window->background->y <= 0) {
            window->background->y = 100;
        } else {
            window->background->y -= SCROLLING_SPEED;
        }
        SDL_BlitSurface(window->bg_top_texture, NULL, window->surface, window->bg_top);

        // draw players
        for (size_t i=0; i<PLAYER_COUNT; ++i) {
            SDL_BlitSurface(state.players[i]->texture[currentAnim/ANIMATION_SLOWDOWN], NULL, window->surface, state.players[i]->image);
        }
        currentAnim++;
        currentAnim == PLAYER_ANIMATIONS * ANIMATION_SLOWDOWN ? currentAnim = 0 : currentAnim;

        // draw or not draw shots
        for (size_t i=0; i<PLAYER_COUNT; ++i) {
            if (state.shotStatus[i]) {
                SDL_BlitSurface(state.shots[i]->texture[0], NULL, window->surface, state.shots[i]->image);
            }
        }

        SDL_BlitSurface(state.tree->texture[0], NULL, window->surface, state.tree->image);

        SDL_UpdateWindowSurface(window->window);
    }
    
}