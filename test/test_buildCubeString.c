#include <zconf.h>
#include <memory.h>
#include <stdio.h>
#include "../include/cube_iproto.h"

#define STR_MAX_LEN 32

int main() {
    const int caseCount = 3;
    char* input[] = {"TCP", "Cube", "MailRu"};
    unsigned char correct[][STR_MAX_LEN] = {
            {0x04, 0x00, 0x00, 0x00, 0x54, 0x43, 0x50, 0x00},
            {0x05, 0x00, 0x00, 0x00, 0x43, 0x75, 0x62, 0x65, 0x00},
            {0x07, 0x00, 0x00, 0x00, 0x4D, 0x61, 0x69, 0x6C, 0x52, 0x75, 0x00}
    };

    char output[STR_MAX_LEN];
    for(int i=0; i<caseCount; i++) {
        buildCubeString(input[i], output);
        if(memcmp(output, correct[i], strlen(input[i]) + 1 +SIZEOF_INT32) != 0) {
            printf("Error in case %d", i);
            return 1;
        }
    }
    return 0;
}
