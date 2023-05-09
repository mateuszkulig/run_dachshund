#ifdef _WIN32
    // windows and mac have needs diffrent types of PORT
    #define PORT "8080"
#else
    #define PORT 8080
#endif

int run_server();