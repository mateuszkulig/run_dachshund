#ifdef _WIN32
    // windows and mac have needs diffrent types of PORT
    #define PORT "8080"
#else
    #define PORT 8080
#endif

#define DEFAULT_BUFLEN 512

#pragma once
#include "client.h"

// initialize server and connect to client socket
platformSocket serverInit();
