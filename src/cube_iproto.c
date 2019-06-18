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

int32_t parseCubeInt32(const char* src) {
    int32_t* num = malloc(SIZEOF_INT32);
    assert(num!=NULL);
    memcpy(num, src, SIZEOF_INT32);
    int32_t result = *num;
    free(num);
    return result;
}

void buildCubeString(const char *src, char *dest) {
    *dest = '0';
    char srcStrLen[SIZEOF_INT32];
    buildCubeInt32((int32_t) strlen(src), srcStrLen);
    memcpy(dest, srcStrLen, SIZEOF_INT32);
    memcpy(dest, src, strlen(src) + 1);
}

char* parseCubeString(const char* src, char* dest) {
    dest = strcpy(src, dest);
    return dest;
}

void cubePkgAppend(char* pkg, size_t shift, char* appendix, const size_t appendixLen) {
    memcpy(pkg+shift, appendix, appendixLen);
    shift += appendixLen;
}

char* buildRequest(const char* token, const char* scope, char* request) {
    char body[BUF_SIZE - 2*SIZEOF_INT32];// Максимальный возможный размер body из заднного API по бнф
    size_t shift = 0;// Текущее смещение в массиве байт body
    char svcMsg[SIZEOF_INT32];
    buildCubeInt32(CUBE_OAUTH2_SVC_MSG, svcMsg);
    memcpy(body, svcMsg, SIZEOF_INT32);
    shift = SIZEOF_INT32;

    size_t cubeTokenLen = strlen(token)+SIZEOF_INT32+1;// 4 доп. байта на длину токена и 1 на \0
    char* cubeToken = malloc(cubeTokenLen);
    assert(cubeToken != NULL);
    buildCubeString(token, cubeToken);
    cubePkgAppend(body, shift, cubeToken, cubeTokenLen);
    free(cubeToken);

    size_t cubeScopeLen = strlen(scope)+SIZEOF_INT32+1;// 4 доп. байта на длину scope и 1 на \0
    char* cubeScope = malloc(cubeScopeLen);
    assert(cubeScope != NULL);
    buildCubeString(scope, cubeScope);
    cubePkgAppend(body, shift, cubeScope, cubeScopeLen);
    free(cubeScope);

    char header[2*SIZEOF_INT32];
    int32_t svcId = CUBE_OAUTH2_SVC_ID;
    buildCubeInt32(svcId, header);

    int32_t bodyLen = (int32_t)shift;
    buildCubeInt32(bodyLen, header + SIZEOF_INT32);

    memcpy(header, request, 2*SIZEOF_INT32);
    memcpy(body, request + 2*SIZEOF_INT32, (size_t)bodyLen);

    return request;
}

char* buildResponse(const char* request, char* response) {
    //TODO develop
    response = strcpy(response, request);
    return response;
}

void printResponse(const char *response) {
    int32_t svcId = parseCubeInt32(response);
    if(svcId != CUBE_OAUTH2_SVC_ID) {
        printf("%s\n", "Error: response contains wrong service id");
        return;
    }

    int32_t bodyLen = parseCubeInt32(response+SIZEOF_INT32);
    const char* body = response + 3*SIZEOF_INT32;

    int32_t returnCode = parseCubeInt32(body);
    if (returnCode != CUBE_OAUTH2_ERR_OK) {
        switch (returnCode) {
            case CUBE_OAUTH2_ERR_TOKEN_NOT_FOUND: {
                printf("error:CUBE_OAUTH2_ERR_TOKEN_NOT_FOUND\n");
                printf("message:%s\n", body+SIZEOF_INT32);
                return;
            }
            case CUBE_OAUTH2_ERR_DB_ERROR: {
                printf("error:CUBE_OAUTH2_ERR_DB_ERROR\n");
                printf("message:%s\n", body+SIZEOF_INT32);
                return;
            }
            case CUBE_OAUTH2_ERR_UNKNOWN_MSG: {
                printf("error:CUBE_OAUTH2_ERR_UNKNOWN_MSG\n");
                printf("message:%s\n", body+SIZEOF_INT32);
                return;
            }
            case CUBE_OAUTH2_ERR_BAD_PACKET: {
                printf("error:CUBE_OAUTH2_ERR_BAD_PACKET\n");
                printf("message:%s\n", body+SIZEOF_INT32);
                return;
            }
            case CUBE_OAUTH2_ERR_BAD_CLIENT: {
                printf("error:CUBE_OAUTH2_ERR_BAD_CLIENT\n");
                printf("message:%s\n", body+SIZEOF_INT32);
                return;
            }
            case CUBE_OAUTH2_ERR_BAD_SCOPE: {
                printf("error:CUBE_OAUTH2_ERR_BAD_SCOPE\n");
                printf("message:%s\n", body+SIZEOF_INT32);
                return;
            }
            default: {
                printf("Error: response contains invalid return code");
                return;
            }
        }
    }

    char* stringBuf = malloc((size_t)bodyLen - 2*SIZEOF_INT32);
    stringBuf = parseCubeString(body + SIZEOF_INT32, stringBuf);// stringBuf ::= <client_id>
    size_t clientIdLen = strlen(stringBuf);
    printf("client_id: %s\n", stringBuf);

    int32_t clientType = parseCubeInt32(body + SIZEOF_INT32 + clientIdLen);
    printf("client_type: %d\n", clientType);

    int32_t expiresIn = parseCubeInt32(body + bodyLen - SIZEOF_INT32);
    printf("expires_in: %d\n", expiresIn);

    stringBuf = parseCubeString(body + 2*SIZEOF_INT32 +clientIdLen, stringBuf);// stringBuf ::= <username>
    printf("username: %s\n", stringBuf);

    free(stringBuf);
}