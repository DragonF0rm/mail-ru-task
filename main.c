#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <memory.h>
#include <netdb.h>
#include <zconf.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include "include/cube_iproto.h"
#include "include/const.h"

int getIpByHostname(const char *hostname, const char* port, char *ip) {
    struct addrinfo hints, *serverInfo;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;

    if (getaddrinfo(hostname, port, &hints, &serverInfo) != 0) {
        return 1;
    }

    strcpy(ip, inet_ntoa(((struct sockaddr_in *) serverInfo->ai_addr)->sin_addr));

    freeaddrinfo(serverInfo);
    return 0;
}

int createSocket(const char* ip, const uint16_t port,  int *sock) {
    *sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); //Дескриптор сокета
    if (*sock < 0) {
        return 1;
    }

    struct sockaddr_in serverInfo; //Адрес сервера, к которому будем подключаться
    memset(&serverInfo, 0, sizeof(serverInfo));
    serverInfo.sin_family = AF_INET;
    serverInfo.sin_port   = htons(port);
    int result = inet_aton(ip, &serverInfo.sin_addr);
    if (result == 0) {
        return 3;
    }

    int connectionResult = connect(*sock, (struct sockaddr *) &serverInfo, sizeof(serverInfo));
    if(connectionResult < 0) {
        return 4;
    }

    return 0;
}

//TODO readme
//TODO tests
int main(int argc, char* argv[]) {
    if (argc != 5) {
        printf("Error: wrong number of arguments");
        printf("Program should be called like: cube <hostname> <port> <token> <scope>");
        return 1;
    }
    char*    host  = argv[1];
    uint16_t port  = (uint16_t)atoi(argv[2]);
    char*    token = argv[3];
    char*    scope = argv[4];

    char ip[16];
    int ipResolvingResult = getIpByHostname(host, argv[2], ip);
    if (ipResolvingResult != 0) {
        printf("Error: unable to resolve hostname to IPv4 address");
        return 2;
    }

    int socket = 0;
    int resultCode = createSocket(ip, port, &socket);
    if (resultCode != 0) {
        printf("Error: unable to create socket, createSocket function finished with code %d\n", resultCode);
        return 3;
    }

    char request[BUF_SIZE];
    buildRequest(token, scope, request);
    write(socket, request, strlen(request) +1);

    char response[BUF_SIZE];
    read(socket, response, port);
    printResponse(response);

    return 0;
}