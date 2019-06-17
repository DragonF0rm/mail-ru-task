#ifndef CUBE_CUBE_PROTO_H
#define CUBE_CUBE_PROTO_H

#include <stdint-gcc.h>
#include "const.h"

void  buildCubeInt32(const int32_t num, char *result);
void  buildCubeString(const char *src, char *dest);
void  cubePkgAppend(char* pkg, size_t shift, char* appendix, const size_t appendixLen);
char* buildRequest(const char* token, const char* scope, char* body);
char* buildResponse(const char* request, char* response);
char* parseResponse(char *response);

#endif //CUBE_CUBE_PROTO_H
