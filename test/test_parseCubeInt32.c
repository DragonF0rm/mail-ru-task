#include <zconf.h>
#include <memory.h>
#include <stdio.h>
#include "../include/cube_iproto.h"

int main() {
    const int caseCount = 3;
    unsigned char input[][SIZEOF_INT32] = {
            {0x00, 0x00, 0x00, 0x00},
            {0x01, 0x00, 0x00, 0x00},
            {0xFF, 0xFF, 0xFF, 0xFF}
    };
    int32_t correct[] = {0, 1, -1};

    int32_t output = 0;
    for(int i=0; i<caseCount; i++) {
        output = parseCubeInt32((char *)input[i]);
        if(output != correct[i]) {
            printf("Error in case %d, expected: %d, got: %d\n", i, correct[i], output);
            return 1;
        }
    }
    return 0;
}
