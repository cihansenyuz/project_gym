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

#define DEV_MODE_USE_PRETAKEN_TOKEN 1   // 1: dev mode, 0: user mode
#define TOKEN "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJlbWFpbCI6ImFkbWluIiwiaWQiOiIwIiwiaWF0IjoxNzIyMjM1Njg3LCJleHAiOjE3MjIyNzg4ODd9.HahI_ep5O_6iP--3GektwucMyqrPtQv1Zd7957dqznY"

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
