#include <stdlib.h>
#include <assert.h>
#include <memory.h>
#include <stdio.h>
#include "../include/cube_iproto.h"

void buildCubeInt32(const int32_t num, char *result) {
    int32_t* numPtr = malloc(sizeof(int32_t));
    assert(numPtr != NULL);
    *numPtr = num;
    memcpy(result, numPtr, sizeof(int32_t));
    free(numPtr);
}

void buildCubeString(const char *src, char *dest) {
    *dest = '0';
    char srcStrLen[4];
    buildCubeInt32((int32_t) strlen(src), srcStrLen);
    memcpy(dest, srcStrLen, 4);
    memcpy(dest, src, strlen(src) + 1);
}

void cubePkgAppend(char* pkg, size_t shift, char* appendix, const size_t appendixLen) {
    memcpy(pkg+shift, appendix, appendixLen);
    shift += appendixLen;
}

char* buildRequest(const char* token, const char* scope, char* request) {
    char body[BUF_SIZE-8];// Максимальный возможный размер body, т.к. длина header - 2 длины int32
    size_t shift = 0;// Текущее смещение в массиве байт body
    char svcMsg[4];
    buildCubeInt32(0x00000001, svcMsg);
    memcpy(body, svcMsg, 4);
    shift = 4;

    size_t cubeTokenLen = strlen(token)+5;// 4 доп. байта на int32 длину токена и 1 на \0
    char* cubeToken = malloc(cubeTokenLen);
    assert(cubeToken != NULL);
    buildCubeString(token, cubeToken);
    cubePkgAppend(body, shift, cubeToken, cubeTokenLen);
    free(cubeToken);

    size_t cubeScopeLen = strlen(scope)+5;// 4 доп. байта на int32 длину scope и 1 на \0
    char* cubeScope = malloc(cubeScopeLen);
    assert(cubeScope != NULL);
    buildCubeString(scope, cubeScope);
    cubePkgAppend(body, shift, cubeScope, cubeScopeLen);
    free(cubeScope);

    char header[8];
    int32_t svcId = 0x00000002;
    buildCubeInt32(svcId, header);

    int32_t bodyLen = (int32_t)shift;
    buildCubeInt32(bodyLen, header + 4);

    memcpy(header, request, 8);
    memcpy(body, request + 8, (size_t)bodyLen);

    return request;
}

char* buildResponse(const char* request, char* response) {
    //TODO develop
    response = strcpy(response, request);
    return response;
}

char* parseResponse(char *response) {
    //TODO develop
    return response;
}