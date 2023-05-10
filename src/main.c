#include "stdio.h"
#include "stdlib.h"

#define SDL_MAIN_HANDLED    // SDL acting up

#include "client.h"
#include "server.h"
#include "engine.h"

void clientServerTest() {
    char buffer;

    printf("please type entity to launch[(c)lient/(s)erver]: ");
    scanf("%c", &buffer);
    printf("your choice is %s\n", buffer == 'c' ? "client" : "server");
    switch (buffer) {
        case 'c':
            {
                char *sendbuf = malloc(DEFAULT_BUFLEN);
                sendbuf = "this is a test!";
                platformSocket sock = clientInit();
                while (getchar() != 'q') {  // getchar takes enter from previous one
                    printf("sending data...\n");
                    sendData(sock, sendbuf);
                    printf("recieving data...\n");
                    printf("recieved data: %s\n", recvData(sock));
                }
                
                killSocket(sock);
                break;
            }
        case 's':
            {   
                char *sendbuf = malloc(DEFAULT_BUFLEN);
                sendbuf = "this is a response!";
                platformSocket sock = serverInit();
                while (getchar() != 'q') {  // getchar takes enter from previous one
                    printf("recieving data...\n");
                    printf("recieved data: %s\n", recvData(sock));
                    printf("sending data...\n");
                    sendData(sock, sendbuf);
                }
                killSocket(sock);
                break;
            }
    }
}

int main(int argc, char **argv) {
    printf("hello dachshund!\n");
    // clientServerTest();
    
    char buffer;

    printf("please type entity to launch[(c)lient/(s)erver]: ");
    scanf("%c", &buffer);
    printf("your choice is %s\n", buffer == 'c' ? "client" : "server");
    switch (buffer) {
        case 'c':
            {
                gameLoop(1);
                break;
            }
        case 's':
            {   
                gameLoop(0);
                break;
            }
    }


    
    

    return 0;
}