#include <memory.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <zconf.h>
#include <stdio.h>
#include <stdbool.h>

#include "server.h"

char * buildResponse(const char* request, char* response) {
    //TODO develop
    response = strcpy(response, request);
    return response;
}

int listenAndServe(uint16_t port, uint16_t msgSize, uint8_t queueLen) {
    struct sockaddr_in addrInfo; //Адрес для привязки к сокету
    memset(&addrInfo, 0, sizeof(addrInfo));
    addrInfo.sin_family      = AF_INET;
    addrInfo.sin_addr.s_addr = htonl(INADDR_ANY);
    addrInfo.sin_port        = htons(port);

    int sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); //Дескриптор сокета
    if (sock < 0) return EXIT_SOCK_ERR;
    int on = 1;
    setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (char *) &on, sizeof(on));
    int bindResult = bind(sock, (struct sockaddr *) &addrInfo, sizeof(addrInfo));
    if (bindResult<0) return EXIT_BIND_ERR;

    int listenResult = listen(sock, queueLen); // Определение размера очереди
    if (listenResult<0) return EXIT_LISTEN_ERR;

    // Сокет установлен и привязан. Ожидание и обработка соединения
    while (1) {
        // Принимаем первое соединение из очереди, получаем дескриптор сокета клиента
        int clientSocket = accept(sock, NULL, NULL);
        if (clientSocket<0) return EXIT_ACCEPT_ERR;

        //Читаем сообщение
        char buf[BUF_SIZE];
        ssize_t bytes = read(clientSocket, buf, BUF_SIZE);
        printf("Incoming message: %s/n",buf);
        write(clientSocket, buf, (size_t)bytes);
        /*ssize_t bytes = 0;
        char buf[BUF_SIZE];
        char* request = "\0";
        do {
            bytes = read(sock, buf, BUF_SIZE);
            strcat(request, buf);
        } while(bytes > 0);

        //Составляем ответ
        char* response = "\0";
        response = buildResponse(request, response);

        //Отправляем ответ клиенту
        bytes = strlen(response);
        int i = 0;
        do {
            strncat(buf, response + BUF_SIZE*i, BUF_SIZE);
            i++;
            bytes -= BUF_SIZE;
        } while(bytes > 0);*/

        close(clientSocket);
    }

    return EXIT_SUCCESS;
}

int main() {
    listenAndServe(PORT, BUF_SIZE, QUERY_LEN);
    return 0;
}
