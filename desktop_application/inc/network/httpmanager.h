#ifndef HTTPMANAGER_H
#define HTTPMANAGER_H

#include "postrequest.h"
#include "getrequest.h"
#include "putrequest.h"

#define DEV_MODE_USE_PRETAKEN_TOKEN 1   // 1: dev mode, 0: user mode
#define TOKEN "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJlbWFpbCI6ImFkbWluIiwiaWQiOiIwIiwiaWF0IjoxNzIxNzM2NjE0LCJleHAiOjE3MjE3Nzk4MTR9.J2M7cA4zAC2C1dJZjI-WK-VTj7xn_SEufm8z2ww3o1I"

class HttpManager : public PostRequest,
                    public GetRequest,
                    public PutRequest
{
public:
    HttpManager();
    QString session_email;
#if DEV_MODE_USE_PRETAKEN_TOKEN
    QString session_token{TOKEN};
#else
    QString session_token{""};
#endif
};

#endif // HTTPMANAGER_H
