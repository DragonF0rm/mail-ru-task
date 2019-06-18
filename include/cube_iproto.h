#ifndef CUBE_CUBE_PROTO_H
#define CUBE_CUBE_PROTO_H

#include <stdint-gcc.h>
#include "const.h"

#define CUBE_OAUTH2_ERR_OK              0x00000000
#define CUBE_OAUTH2_ERR_TOKEN_NOT_FOUND 0x00000001
#define CUBE_OAUTH2_ERR_DB_ERROR        0x00000002
#define CUBE_OAUTH2_ERR_UNKNOWN_MSG     0x00000003
#define CUBE_OAUTH2_ERR_BAD_PACKET      0x00000004
#define CUBE_OAUTH2_ERR_BAD_CLIENT      0x00000005
#define CUBE_OAUTH2_ERR_BAD_SCOPE       0x00000006

#define CUBE_OAUTH2_SVC_ID  0x00000002
#define CUBE_OAUTH2_SVC_MSG 0x00000001

#define SIZEOF_INT32 4

void    buildCubeInt32(const int32_t num, char *result);
int32_t parseCubeInt32(const char* src);
void    buildCubeString(const char *src, char *dest);
size_t  parseCubeString(const char* src, char* dest);
void    cubePkgAppend(char* pkg, size_t* shift, char* appendix, const size_t appendixLen);
char*   buildRequest(const char* token, const char* scope, char* request);
void    printResponse(const char *response);

#endif //CUBE_CUBE_PROTO_H
