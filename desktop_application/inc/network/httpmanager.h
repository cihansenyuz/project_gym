#ifndef HTTPMANAGER_H
#define HTTPMANAGER_H

#include "postrequest.h"
#include "getrequest.h"
#include "putrequest.h"

#define DEV_MODE_USE_PRETAKEN_TOKEN 1   // 1: dev mode, 0: user mode
#define TOKEN "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJlbWFpbCI6ImFkbWluIiwiaWQiOiIwIiwiaWF0IjoxNzIxNjYyMDUzLCJleHAiOjE3MjE3MDUyNTN9.Ct13wZ_UVO3YxaZPffAW-6h7Dnw6iC7qOJm3E_ZzXSE"

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
    QString token{""};
#endif
};

#endif // HTTPMANAGER_H
