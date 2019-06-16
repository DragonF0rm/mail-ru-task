#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <memory.h>
#include <netdb.h>
#include <zconf.h>
#include <stdlib.h>
#include <arpa/inet.h>

#define HOST  "localhost\0"
#define PORT  5000
#define TOKEN "abracadabra\0"
#define SCOPE "test\0"
#define BUF_SIZE 4096

int createSocket(int *sock) {
    *sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); //Дескриптор сокета
    if (*sock < 0) {
        return 1;
    }

    struct hostent* hostInfo = gethostbyname(HOST); //Получаем IP и прочую информацию о сервре
    if (!hostInfo) {
        return 2;
    }

    struct sockaddr_in serverInfo; //Адрес сервера, к которому будем подключаться
    memset(&serverInfo, 0, sizeof(serverInfo));
    serverInfo.sin_family = AF_INET;
    serverInfo.sin_port   = htons(PORT);
    int result = inet_aton("127.0.0.1", &serverInfo.sin_addr);
    if (result == 0) {
        return 3;
    }

    int connectionResult = connect(*sock, (struct sockaddr *) &serverInfo, sizeof(serverInfo));
    if(connectionResult < 0) {
        return 4;
    }

    return 0;
}

int main() {
    int socket = 0;
    int resultCode = createSocket(&socket);
    if (resultCode != 0) {
        printf("Error: unable to create socket, createSocket function finished with code %d\n", resultCode);
        return 1;
    }

    write(socket, TOKEN, strlen(TOKEN) +1);
    while(1) {
        char buf[BUF_SIZE];
        ssize_t bytes = read(socket, buf, 5000);
        if (bytes <= 0) {
            return 0;
        }
        write(1, buf, (size_t)bytes);
    }

    return 0;
}