#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <memory.h>
#include <netdb.h>
#include <zconf.h>
#include <stdlib.h>
#include <arpa/inet.h>

#define BUF_SIZE 4096

int createSocket(const char* host, const uint16_t port,  int *sock) {
    *sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); //Дескриптор сокета
    if (*sock < 0) {
        return 1;
    }

    //TODO get ip by hostname

    struct sockaddr_in serverInfo; //Адрес сервера, к которому будем подключаться
    memset(&serverInfo, 0, sizeof(serverInfo));
    serverInfo.sin_family = AF_INET;
    serverInfo.sin_port   = htons(port);
    int result = inet_aton(host, &serverInfo.sin_addr);
    if (result == 0) {
        return 3;
    }

    int connectionResult = connect(*sock, (struct sockaddr *) &serverInfo, sizeof(serverInfo));
    if(connectionResult < 0) {
        return 4;
    }

    return 0;
}

char* buildRequest(const char* token, const char* scope, char* request) {
    //TODO develop
    *request = '\0';
    request = strcat(request, token);
    request = strcat(request, scope);
    return request;
}

void printResponse(const char* response) {
    //TODO develop
    printf("%s\n", response);
}

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

    int socket = 0;
    int resultCode = createSocket(host, port, &socket);
    if (resultCode != 0) {
        printf("Error: unable to create socket, createSocket function finished with code %d\n", resultCode);
        return 2;
    }

    char request[BUF_SIZE];
    buildRequest(token, scope, request);

    write(socket, request, strlen(request) +1);
    while(1) {
        char buf[BUF_SIZE];
        char* response = "\0";
        ssize_t bytes = read(socket, buf, BUF_SIZE);
        if (bytes <= 0) {
            printResponse(response);
            return 0;
        } else {
            strcat(response, buf);
        }
    }
}