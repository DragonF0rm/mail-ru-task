#include <zconf.h>
#include <memory.h>
#include <stdio.h>
#include "../include/cube_iproto.h"

#define STR_MAX_LEN 32

int main() {
    const int caseCount = 3;
    unsigned char input[][STR_MAX_LEN] = {
            {0x04, 0x00, 0x00, 0x00, 0x54, 0x43, 0x50, 0x00},
            {0x05, 0x00, 0x00, 0x00, 0x43, 0x75, 0x62, 0x65, 0x00},
            {0x07, 0x00, 0x00, 0x00, 0x4D, 0x61, 0x69, 0x6C, 0x52, 0x75, 0x00}
    };
    char*  correct[] = {"TCP", "Cube", "MailRu"};

    char output[STR_MAX_LEN];
    for(int i=0; i<caseCount; i++) {
        size_t parsedPartLen = parseCubeString((char*)input[i], output);
        if(strcmp(output, correct[i]) != 0) {
            printf("Error in case %d, expected: %s, got: %s\n", i, correct[i], output);
            return 1;
        }

        size_t correctStrLen = strlen(correct[i]) + 1 +SIZEOF_INT32;
        if(parsedPartLen != correctStrLen) {
            printf("Error in case %d, strLen expected: %ld, got: %ld\n", i, correctStrLen, parsedPartLen);
            return 2;
        }
    }
    return 0;
}

