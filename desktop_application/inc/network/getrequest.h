#ifndef GETREQUEST_H
#define GETREQUEST_H

#include "networkcore.h"

class GetRequest : public NetworkCore
{
    Q_OBJECT
public:
    GetRequest();
    void FetchMemberJsonData();

signals:
    void MemberJsonFetched();

private slots:
    void OnFetchMemberJsonDataReplyRecieved();

private:
    QNetworkReply* GetHttpReply(const QNetworkRequest &request) override;
};

#endif // GETREQUEST_H
