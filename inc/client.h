#ifdef _WIN32
    #include "WinSock2.h"
#else
    #define SOCKET struct SOCKET {}
#endif
#define LOCALHOST "127.0.0.1"

typedef struct platformSocket {
    SOCKET  winSocket;
    int     macSocket;
} platformSocket;

// test function
int run();

// initialize client socket
platformSocket clientInit();

// send data to socket
void sendData(platformSocket sock, const char *sendbuf);

// socket shutdown and freeup
void killSocket(platformSocket sock);
