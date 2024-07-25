#ifndef HTTPMANAGER_H
#define HTTPMANAGER_H

#include "postrequest.h"
#include "getrequest.h"
#include "putrequest.h"

#define DEV_MODE_USE_PRETAKEN_TOKEN 1   // 1: dev mode, 0: user mode
#define TOKEN "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJlbWFpbCI6ImFkbWluIiwiaWQiOiIwIiwiaWF0IjoxNzIxODkzMjY5LCJleHAiOjE3MjE5MzY0Njl9.gSkYAYwc6l8710BokO2MIaijozQUPdNYyFryoBmG9oo"

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
