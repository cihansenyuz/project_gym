#ifndef HTTPMANAGER_H
#define HTTPMANAGER_H

#include "postrequest.h"
#include "getrequest.h"
#include "putrequest.h"

class HttpManager : public PostRequest,
                    public GetRequest,
                    public PutRequest
{
public:
    HttpManager() = default;
};

#endif // HTTPMANAGER_H
