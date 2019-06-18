#include <stdio.h>
#include <memory.h>
#include "../include/cube_iproto.h"

int main() {
    char* inputToken = "Token";
    char* inputScope = "test";
    unsigned char correct[] = {
            0x02, 0x00, 0x00, 0x00, // <svc_id>
            0x17, 0x00, 0x00, 0x00, // <body_length>
            0x01, 0x00, 0x00, 0x00, // <svc_msg>
            0x06, 0x00, 0x00, 0x00, /*<str_len>*/ 0x54, 0x6F, 0x6B, 0x65, 0x6E, 0x00, //<token>
            0x05, 0x00, 0x00, 0x00, /*<str_len>*/ 0x74, 0x65, 0x73, 0x74, 0x00 //<scope>
    };

    const size_t requestLen = sizeof(correct);
    char output[requestLen];

    buildRequest(inputToken, inputScope, output);
    if(memcmp(output, correct, requestLen) != 0) {
        printf("Error: unexpected request\n");
        printf("Expected | Got\n");
        for(int i=0; i<requestLen; i++) {
            printf("%c | %c\n", correct[i], output[i]);
        }
        return 1;
    }

    return 0;
}