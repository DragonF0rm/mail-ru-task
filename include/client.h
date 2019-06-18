#ifndef CUBE_CLIENT_H
#define CUBE_CLIENT_H

#include <stdint-gcc.h>
#include "../include/const.h"
#include "../include/cube_iproto.h"

int getIpByHostname(const char *hostname, const char* port, char *ip);
int createSocket(const char* ip, const uint16_t port,  int *sock);

#endif //CUBE_CLIENT_H
