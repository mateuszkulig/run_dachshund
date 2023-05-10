#ifdef _WIN32
    #include "WinSock2.h"
    // windows and mac have needs diffrent types of PORT
    #define PORT "8080"
#else
    #define SOCKET struct SOCKET {}
    #define PORT 8080
#endif
#define LOCALHOST   "127.0.0.1"

#pragma once


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

// get data from socket
void recvData(platformSocket sock);

// socket shutdown and freeup
void killSocket(platformSocket sock);

