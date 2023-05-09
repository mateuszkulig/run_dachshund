#include "stdio.h"
#include "stdlib.h"
#include "client.h"
#include "server.h"

int main(int argc, char **argv) {
    char buffer;

    printf("hello dachshund!\n");
    printf("please type entity to launch[(c)lient/(s)erver]: ");
    scanf("%c", &buffer);
    printf("your choice is %s\n", buffer == 'c' ? "client" : "server");
    switch (buffer) {
        case 'c':
            {
                char *sendbuf = malloc(16);
                sendbuf = "this is a test!";
                platformSocket sock = clientInit();
                while (getchar() != 'q') {  // getchar takes enter from previous one
                    printf("sending data...\n");
                    sendData(sock, sendbuf);
                }
                
                killSocket(sock);
                break;
            }
        case 's':
            {   
                run_server();
                break;
            }
    }

    return 0;
}