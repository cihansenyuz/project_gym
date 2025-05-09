/**
  ******************************************************************************
  * @file    httpmanager.hpp
  * @author  Cihan Senyuz
  * @date    12.07.2024
  * @brief   Header for HttpManager class.
  *          This file contains the definition of the HttpManager class, which
  *          inherits from PostRequest, GetRequest, and PutRequest classes to
  *          manage various HTTP requests using a single interface.
  *
  * @note    define DEV_MODE_USE_PRETAKEN_TOKEN and TOKEN to skip getting a new
  *          token upon each log in.
  ******************************************************************************
  */

#ifndef HTTPMANAGER_H
#define HTTPMANAGER_H

#include "postrequest.h"
#include "getrequest.h"
#include "putrequest.h"
#include "deleterequest.h"

#ifndef TOKEN
    #define TOKEN ""
#endif

class HttpManager : public PostRequest,
                    public GetRequest,
                    public PutRequest,
                    public DeleteRequest
{
public:
    HttpManager();
    QString token{TOKEN};
};

#endif // HTTPMANAGER_H
