#include <memory.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <zconf.h>
#include <stdio.h>
#include <stdbool.h>

#define EXIT_SUCCESS    0
#define EXIT_SOCK_ERR   1
#define EXIT_BIND_ERR   2
#define EXIT_LISTEN_ERR 3
#define EXIT_ACCEPT_ERR 4
char* EXIT_MSG[] = {
        "Function successfully finished",
        "Error: unable to create socket",
        "Error: unable to bind to socket",
        "Error: unable to listen socket",
        "Error: unable to accept TCP connection"
};

bool server = true;

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
        char buf[msgSize];
        read(clientSocket, buf, msgSize);
        printf("%s\n", buf);

        close(clientSocket);
    }

    return EXIT_SUCCESS;
}

int main() {
    listenAndServe(5000, 4096, 10);
    return 0;
}
