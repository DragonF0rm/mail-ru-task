#include <zconf.h>
#include <memory.h>
#include <stdio.h>
#include "../include/cube_iproto.h"

int main() {
    const int caseCount = 3;
    int32_t input[] = {0, 1, -1};
    unsigned char correct[][SIZEOF_INT32] = {
            {0x00, 0x00, 0x00, 0x00},
            {0x01, 0x00, 0x00, 0x00},
            {0xFF, 0xFF, 0xFF, 0xFF}
    };

    char output[SIZEOF_INT32];
    for(int i=0; i<caseCount; i++) {
        buildCubeInt32(input[i], output);
        if(memcmp(output, correct[i], SIZEOF_INT32) != 0) {
            printf("Error in case %d", i);
            return 1;
        }
    }
    return 0;
}