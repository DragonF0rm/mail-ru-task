#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <memory.h>
#include <netdb.h>
#include <zconf.h>
#include <stdlib.h>

#include "server-mock/server.h"

#define HOST  "cube.testserver.mail.ru\0"
#define PORT  4995
#define TOKEN "abracadabra\0"
#define SCOPE "test\0"

int main() {
    listenAndServe(5000, 4096, 10);
    /*int sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); //Дескриптор сокета
    if (sock < 0) {
        printf("Error: unable to create new socket\n");
        return 1;
    }
    printf("Socket created\n");

    struct hostent* hostInfo = gethostbyname(HOST); //Получаем IP и прочую информацию о сервре
    if (!hostInfo) {
        printf("Error: unable to resolve HOST: %s\n", HOST);
        return 1;
    }
    printf("IP resolved: %s\n", hostInfo->h_aliases[0]);

    struct sockaddr_in serverInfo; //Адрес сервера, к которому будем подключаться
    memset(&serverInfo, 0, sizeof(serverInfo));
    serverInfo.sin_family = AF_INET;
    memcpy(&serverInfo.sin_addr, hostInfo->h_addr_list[0], sizeof(*hostInfo->h_addr_list[0]));
    serverInfo.sin_port   = htons(PORT);
    printf("Server address created\n");

    int connectionResult = connect(sock, (struct sockaddr *) &serverInfo, sizeof(serverInfo));
    if(connectionResult < 0) {
        printf("Error: connection failed\n");
        return 1;
    }
    printf("Connected to server\n");

    write(sock, TOKEN, strlen(TOKEN) +1);
    printf("Token sent\n");

    while(1) {
        char buf[1000];
        ssize_t bytes = read(sock, buf, 1000);
        if (bytes <= 0) {
            return 0;
        }
        write(1, buf, (size_t)bytes);
    }*/
}