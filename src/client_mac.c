#include <arpa/inet.h> // inet_addr()
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h> // bzero()
#include <sys/socket.h>
#include <unistd.h> // read(), write(), close()

#include "client.h"

#define SA struct sockaddr

platformSocket clientInit() {
    int sockfd, connfd;
    struct sockaddr_in servaddr, cli;
    platformSocket sock;
 
    // socket create and verification
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        printf("socket creation failed...\n");
        exit(0);
    }
    bzero(&servaddr, sizeof(servaddr));
 
    // assign IP, PORT
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr(LOCALHOST);
    servaddr.sin_port = htons(PORT);
 
    // connect the client socket to server socket
    if (connect(sockfd, (SA*)&servaddr, sizeof(servaddr))
        != 0) {
        printf("connection with the server failed...\n");
        exit(0);
    }
    
    sock.macSocket = sockfd;
    return sock;
}

void sendData(platformSocket sock, const char *sendbuf) {
    write(sock.macSocket, sendbuf, DEFAULT_BUFLEN);
}

char *recvData(platformSocket sock) {
    char *buffer = malloc(DEFAULT_BUFLEN);
    recv(sock.macSocket, buffer, DEFAULT_BUFLEN, 0);
    return buffer;
}

void killSocket(platformSocket sock) {
    close(sock.macSocket);
}