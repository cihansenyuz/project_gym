#ifndef HTTPMANAGER_H
#define HTTPMANAGER_H

#include "postrequest.h"
#include "getrequest.h"
#include "putrequest.h"

#define DEV_MODE_USE_PRETAKEN_TOKEN 1   // 1: dev mode, 0: user mode
#define TOKEN "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJlbWFpbCI6ImFkbWluIiwiaWQiOiIwIiwiaWF0IjoxNzIxOTczNzA2LCJleHAiOjE3MjIwMTY5MDZ9.1oxPnjitOuHV5Xy6ukIyfzOGG1AyKI7wdhlru3s-WVM"

class HttpManager : public PostRequest,
                    public GetRequest,
                    public PutRequest
{
public:
    HttpManager();
#if DEV_MODE_USE_PRETAKEN_TOKEN
    QString token{TOKEN};
#else
    QString token{""};
#endif
};

#endif // HTTPMANAGER_H
