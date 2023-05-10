#include "encoder_decoder.h"

char *zeroFill(int number) {
    char *result = malloc(3);
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

char *encode(playerData player) {
    char    *result = calloc(DEFAULT_BUFLEN, 1);
    int     count = 0;
    char    *bufferTop, *bufferLeft, *bufferBottom, *bufferRight, *bufferImgX, *bufferImgY;
    
    bufferTop = zeroFill(player.top);
    bufferLeft = zeroFill(player.left);
    bufferBottom = zeroFill(player.bottom);
    bufferRight = zeroFill(player.right);
    bufferImgX = zeroFill(player.image->x);
    bufferImgY = zeroFill(player.image->y);

    for(size_t i=0; i<3; ++i) {
        result[i] = bufferTop[i];
        result[i+3] = bufferLeft[i];
        result[i+6] = bufferBottom[i];
        result[i+9] = bufferRight[i];
        result[i+12] = bufferImgX[i];
        result[i+15] = bufferImgY[i];
    }
    result[18] = '\0';

    free(bufferTop);
    free(bufferLeft);
    free(bufferBottom);
    free(bufferRight);
    free(bufferImgX);
    free(bufferImgY);

    

    return result;
}
