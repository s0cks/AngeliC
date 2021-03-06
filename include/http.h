#ifndef ANGELIC_HTTP_H
#define ANGELIC_HTTP_H

#include "buffer.h"

#ifndef __attribute__
#define __attribute__(x)
#endif

struct angelic_http_header{
    angelic_buffer* key;
    angelic_buffer* value;
};

typedef struct angelic_http_header angelic_http_header;

angelic_http_header* angelic_http_header_malloc(const char* key, const char* value) __attribute__((malloc));
void angelic_http_header_free(angelic_http_header* header);
angelic_buffer* angelic_http_header_cstr(angelic_http_header* header);

struct angelic_http_response{
    angelic_http_header* headers[100];
    size_t headers_len;
    int status;
    angelic_buffer* title;
    angelic_buffer* content;
};

typedef struct angelic_http_response angelic_http_response;

angelic_http_response* angelic_http_response_malloc(int status, const char* title) __attribute__((malloc));
void angelic_http_response_free(angelic_http_response* response);
void angelic_http_response_add_header(angelic_http_response* response, const char* key, const char* value);
angelic_buffer* angelic_http_response_cstr(angelic_http_response* response);

struct angelic_http_request{
    angelic_http_header* headers[100];
    size_t headers_len;
    angelic_buffer* method;
    angelic_buffer* route;
    angelic_buffer* body;
};

typedef struct angelic_http_request angelic_http_request;

angelic_http_request* angelic_http_request_malloc() __attribute__((malloc));
void angelic_http_request_add_header(angelic_http_request* request, angelic_http_header* header);
void angelic_http_request_free(angelic_http_request* request);

struct angelic_http_request_parser{
    size_t pos;
    angelic_buffer* content;
};

typedef struct angelic_http_request_parser angelic_http_request_parser;

angelic_http_request_parser* angelic_http_request_parser_malloc(angelic_buffer* ib) __attribute__((malloc));
angelic_http_request* angelic_http_request_parser_parse(angelic_http_request_parser* parser);
void angelic_http_request_parser_free(angelic_http_request_parser* parser);

#endif