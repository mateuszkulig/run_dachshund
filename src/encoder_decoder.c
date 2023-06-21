#include "encoder_decoder.h"

char *zeroFill(int number) {
    char *result = malloc(3);
    if (number <= 0) {
        result[0] = '0';
        result[1] = '0';
        result[2] = '0';
        return result;
    }

    if (number < 10) {
        result[0] = '0';
        result[1] = '0';
        result[2] = number + '0';
    } else if (number < 100) {
        result[0] = '0';
        result[1] = (number / 10) + '0';
        result[2] = number - ((number / 10) * 10) + '0';
    } else {
        result[0] = (number / 100) + '0';
        result[1] = (number - (number / 100) * 100) / 10 + '0';
        result[2] = number - (number / 10) * 10 + '0';
    }

    return result;
}

char *encode(playerData *player, playerData *shot, playerData *tree, int *shotStatus) {
    char    *result = calloc(DEFAULT_BUFLEN, 1);
    char    *bufferTop, *bufferLeft, *bufferBottom, *bufferRight, *bufferImgX, *bufferImgY,
            *bufferShotTop, *bufferShotLeft, *bufferShotBottom, *bufferShotRight, *bufferShotImgX, *bufferShotImgY,
            *bufferShotStatus,
            *bufferTreeTop, *bufferTreeLeft, *bufferTreeBottom, *bufferTreeRight, *bufferTreeImgX, *bufferTreeImgY;
    
    bufferTop = zeroFill(player->top);
    bufferLeft = zeroFill(player->left);
    bufferBottom = zeroFill(player->bottom);
    bufferRight = zeroFill(player->right);
    bufferImgX = zeroFill(player->image->x);
    bufferImgY = zeroFill(player->image->y);

    bufferShotTop = zeroFill(shot->top);
    bufferShotLeft = zeroFill(shot->left);
    bufferShotBottom = zeroFill(shot->bottom);
    bufferShotRight = zeroFill(shot->right);
    bufferShotImgX = zeroFill(shot->image->x);
    bufferShotImgY = zeroFill(shot->image->y);

    bufferShotStatus = zeroFill(*shotStatus);

    bufferTreeTop = zeroFill(tree->top);
    bufferTreeLeft = zeroFill(tree->left);
    bufferTreeBottom = zeroFill(tree->bottom);
    bufferTreeRight = zeroFill(tree->right);
    bufferTreeImgX = zeroFill(tree->image->x);
    bufferTreeImgY = zeroFill(tree->image->y);

    for(size_t i=0; i<3; ++i) {
        result[i] = bufferTop[i];
        result[i+3] = bufferLeft[i];
        result[i+6] = bufferBottom[i];
        result[i+9] = bufferRight[i];
        result[i+12] = bufferImgX[i];
        result[i+15] = bufferImgY[i];

        result[i+18] = bufferShotTop[i];
        result[i+21] = bufferShotLeft[i];
        result[i+24] = bufferShotBottom[i];
        result[i+27] = bufferShotRight[i];
        result[i+30] = bufferShotImgX[i];
        result[i+33] = bufferShotImgY[i];

        result[i+36] = bufferShotStatus[i];

        result[i+39] = bufferTreeTop[i];
        result[i+42] = bufferTreeLeft[i];
        result[i+45] = bufferTreeBottom[i];
        result[i+48] = bufferTreeRight[i];
        result[i+51] = bufferTreeImgX[i];
        result[i+54] = bufferTreeImgY[i];
    }

    result[57] = '\0';

    free(bufferTop);
    free(bufferLeft);
    free(bufferBottom);
    free(bufferRight);
    free(bufferImgX);
    free(bufferImgY);

    free(bufferShotTop);
    free(bufferShotLeft);
    free(bufferShotBottom);
    free(bufferShotRight);
    free(bufferShotImgX);
    free(bufferShotImgY);

    free(bufferShotStatus);

    free(bufferTreeTop);
    free(bufferTreeLeft);
    free(bufferTreeBottom);
    free(bufferTreeRight);
    free(bufferTreeImgX);
    free(bufferTreeImgY);

    return result;
}

void decode(playerData *player, playerData *shot, playerData *tree, char *code, int *shotStatus) {
    char    bufferTop[4], bufferLeft[4], bufferBottom[4], bufferRight[4], bufferImgX[4], bufferImgY[4],
            bufferShotTop[4], bufferShotLeft[4], bufferShotBottom[4], bufferShotRight[4], bufferShotImgX[4], bufferShotImgY[4],
            bufferShotStatus[4],
            bufferTreeTop[4], bufferTreeLeft[4], bufferTreeBottom[4], bufferTreeRight[4], bufferTreeImgX[4], bufferTreeImgY[4];
        
    bufferTop[3] = '\0';
    bufferLeft[3] = '\0';
    bufferBottom[3] = '\0';
    bufferRight[3] = '\0';
    bufferImgX[3] = '\0';
    bufferImgY[3] = '\0';

    bufferShotTop[3] = '\0';
    bufferShotLeft[3] = '\0';
    bufferShotBottom[3] = '\0';
    bufferShotRight[3] = '\0';
    bufferShotImgX[3] = '\0';
    bufferShotImgY[3] = '\0';

    bufferShotStatus[3] = '\0';

    bufferTreeTop[3] = '\0';
    bufferTreeLeft[3] = '\0';
    bufferTreeBottom[3] = '\0';
    bufferTreeRight[3] = '\0';
    bufferTreeImgX[3] = '\0';
    bufferTreeImgY[3] = '\0';

    for(size_t i=0; i<3; ++i) {
        bufferTop[i] = code[i];
        bufferLeft[i] = code[i+3];
        bufferBottom[i] = code[i+6];
        bufferRight[i] = code[i+9];
        bufferImgX[i] = code[i+12];
        bufferImgY[i] = code[i+15];

        bufferShotTop[i] = code[i+18];
        bufferShotLeft[i] = code[i+21];
        bufferShotBottom[i] = code[i+24];
        bufferShotRight[i] = code[i+27];
        bufferShotImgX[i] = code[i+30];
        bufferShotImgY[i] = code[i+33];

        bufferShotStatus[i] = code[i+36];

        bufferTreeTop[i] = code[i+39];
        bufferTreeLeft[i] = code[i+42];
        bufferTreeBottom[i] = code[i+45];
        bufferTreeRight[i] = code[i+48];
        bufferTreeImgX[i] = code[i+51];
        bufferTreeImgY[i] = code[i+54];
    }

    player->top = atoi(bufferTop);
    player->left = atoi(bufferLeft);
    player->bottom = atoi(bufferBottom);
    player->right = atoi(bufferRight);
    player->image->x = atoi(bufferImgX);
    player->image->y = atoi(bufferImgY);

    shot->top = atoi(bufferShotTop);
    shot->left = atoi(bufferShotLeft);
    shot->bottom = atoi(bufferShotBottom);
    shot->right = atoi(bufferShotRight);
    shot->image->x = atoi(bufferShotImgX);
    shot->image->y = atoi(bufferShotImgY);

    *shotStatus = atoi(bufferShotStatus);

    tree->top = atoi(bufferTreeTop);
    tree->left = atoi(bufferTreeLeft);
    tree->bottom = atoi(bufferTreeBottom);
    tree->right = atoi(bufferTreeRight);
    tree->image->x = atoi(bufferTreeImgX);
    tree->image->y = atoi(bufferTreeImgY);

    free(code);
}
