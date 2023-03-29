#include "stdio.h"
#include "client.h"

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
                while (1) {
                    printf("sending data...\n");
                    sendData(sock, sendbuf);
                    printf("press enter to send more data");
                    getchar();
                }
                
                killSocket(sock);
                break;
            }
        case 's':
            {   
                // launch server
                break;
            }
    }

    return 0;
}