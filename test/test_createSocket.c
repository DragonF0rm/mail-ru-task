#include <memory.h>
#include <stdio.h>
#include <assert.h>
#include <zconf.h>
#include "../include/client.h"
#include "../include/server-mock.h"

int main() {
    //Будем считать, что функция createSocket работает верно,
    //если через полученный из неё сокет можно подключиться к серверу и
    //получить от него заданный ответ
    char* inputIp  = "127.0.0.1";
    char* inputPkg = "Request";
    char* correct  = "Response";
    struct serveArgs args = {strlen(correct) + 1, correct}; //Response для сервера
    startNewThreadServer(&args);

    int socket = 0;
    createSocket(inputIp, PORT, &socket);
    assert(socket != 0);

    write(socket, inputPkg, strlen(inputPkg) + 1);
    char output[BUF_SIZE];
    read(socket, output, BUF_SIZE);

    if(strcmp(output, correct) != 0) {
        printf("Error: server returned wrong response, expected: %s, got: %s\n", correct, output);
        return 1;
    }
    return 0;
};