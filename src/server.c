#include <memory.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <zconf.h>
#include <stdio.h>
#include <stdbool.h>

#include "../include/server.h"

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
        char request[msgSize];
        read(clientSocket, request, msgSize);

        char response[BUF_SIZE];
        buildResponse(request, response);
        write(clientSocket, response, strlen(response) + 1);

        close(clientSocket);
    }

    return EXIT_SUCCESS;
}

int main() {
    listenAndServe(PORT, BUF_SIZE, QUERY_LEN);
    return 0;
}
