#include "stdio.h"
#include "stdlib.h"
#include "engine.h"
#include "server.h"

// create 3 byte char from up to 3 digits number
char *zeroFill(int number);

// encode player data into string
char *encode(playerData *player, playerData *shot, playerData *tree, int *shotsStatus);

// set up player with decoded data
void decode(playerData *player, playerData *shot, playerData *tree, char *code, int *shotStatus, int playerNumber);
