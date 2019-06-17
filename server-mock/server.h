//
// Created by maxim on 16.06.19.
//

#ifndef CUBE_SERVER_H
#define CUBE_SERVER_H

#include <stdint.h>

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

#define PORT      5000
#define BUF_SIZE  1024
#define QUERY_LEN 10

int listenAndServe(uint16_t port, uint16_t msgSize, uint8_t queueLen);

#endif //CUBE_SERVER_H
