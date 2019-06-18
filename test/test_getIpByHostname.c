#include <memory.h>
#include <stdio.h>
#include "../include/client.h"
#include "../include/server-mock.h"

int main() {
    char ip[16];
    const int caseCount = 3;
    char* inputHost[] = {"localhost", "127.0.0.1", "94.100.180.200"};
    char* inputPort[] = {PORT_STR, PORT_STR, "http"};
    char* correct[]   = {"127.0.0.1", "127.0.0.1", "94.100.180.200"};

    struct serveArgs args = {1,""}; //Response для сервера, в данном тесте не имеет значения
    startNewThreadServer(&args); //Поднимаем сервер, чтобы ip определился

    for(int i=0;i<caseCount;i++) {
        getIpByHostname(inputHost[i], inputPort[i], ip);
        if(strcmp(ip, correct[i]) != 0) {
            printf("Error in case %d, expected: %s, got: %s\n", i, correct[i], ip);
            return 1;
        }
    }

    return 0;
};
