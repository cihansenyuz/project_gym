/**
  ******************************************************************************
  * @file    putrequest.hpp
  * @author  Cihan Senyuz
  * @date    14.07.2024
  * @brief   Header for PutRequest class.
  *          This file contains the definition of the PutRequest class, which
  *          extends NetworkCore to manage HTTP PUT requests for pushing member
  *          JSON data.
  ******************************************************************************
  */

#ifndef PUTREQUEST_H
#define PUTREQUEST_H

#include "networkcore.h"

class PutRequest : public NetworkCore
{
    Q_OBJECT
public:
    PutRequest(HttpManager *parent = nullptr);
    void PushMemberJsonData(const QJsonObject &data_to_push);

private slots:
    void OnPushMemberJsonDataReplyRecieved();

private:
    QNetworkReply* GetHttpReply(const QNetworkRequest &request) override;
    HttpManager *parent_;
};

#endif // PUTREQUEST_H
