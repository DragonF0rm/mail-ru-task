#ifndef CUBE_SERVER_H
#define CUBE_SERVER_H

#include <stdint.h>

int listenAndServe(uint16_t port, uint16_t msgSize, uint8_t queueLen);

#endif //CUBE_SERVER_H
