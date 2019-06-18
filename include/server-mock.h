#ifndef CUBE_SERVER_H
#define CUBE_SERVER_H

#include <stdint-gcc.h>
#include "const.h"
#include "../include/cube_iproto.h"

#define EXIT_SUCCESS    0
#define EXIT_SOCK_ERR   1
#define EXIT_BIND_ERR   2
#define EXIT_LISTEN_ERR 3
#define EXIT_ACCEPT_ERR 4
#define EXIT_THREAD_ERR 5

#define PORT      5000
#define PORT_STR  "5000"
#define QUERY_LEN 10

struct serveArgs {
    size_t responseLen;
    char* response;
};

void* startNewThreadServer(struct serveArgs * args);

#endif //CUBE_SERVER_H
