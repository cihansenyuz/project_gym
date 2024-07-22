#ifndef HTTPMANAGER_H
#define HTTPMANAGER_H

#include "postrequest.h"
#include "getrequest.h"
#include "putrequest.h"

#define GIVE_PRETAKEN_TOKEN 1
#define TOKEN "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJlbWFpbCI6ImFkbWluIiwiaWQiOiIwIiwiaWF0IjoxNzIxNjYyMDUzLCJleHAiOjE3MjE3MDUyNTN9.Ct13wZ_UVO3YxaZPffAW-6h7Dnw6iC7qOJm3E_ZzXSE"

class HttpManager : public PostRequest,
                    public GetRequest,
                    public PutRequest
{
public:
    HttpManager();
#if GIVE_PRETAKEN_TOKEN
    QString token{TOKEN};
#else
    QString token{""};
#endif
};

#endif // HTTPMANAGER_H
