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
                const char *sendbuf = "this is a test";
                platformSocket sock = clientInit();
                sendData(sock, sendbuf);
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