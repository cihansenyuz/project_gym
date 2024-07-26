/**
  ******************************************************************************
  * @file    getrequest.hpp
  * @author  Cihan Senyuz
  * @date    14.07.2024
  * @brief   Header for GetRequest class.
  *          This file contains the definition of the GetRequest class, which
  *          extends NetworkCore to manage HTTP GET requests specifically for
  *          fetching member JSON data.
  *
  ******************************************************************************
  */

#ifndef GETREQUEST_H
#define GETREQUEST_H

#include "networkcore.h"

class GetRequest : public NetworkCore
{
    Q_OBJECT
public:
    GetRequest(HttpManager *parent = nullptr);
    void FetchMemberJsonData();

signals:
    void MemberJsonFetched(const std::unique_ptr<QJsonArray> &fetched_data);

private slots:
    void OnFetchMemberJsonDataReplyRecieved();

private:
    QNetworkReply* GetHttpReply(const QNetworkRequest &request) override;
    HttpManager *parent_;
};

#endif // GETREQUEST_H
