#include <stdio.h>
#include <stdint-gcc.h>
#include <stdlib.h>
#include <memory.h>
#include <zconf.h>
#include "../include/client.h"

//TODO readme
//TODO tests
//TODO main.sh
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
    read(socket, response, BUF_SIZE);
    printResponse(response);

    return 0;
}
