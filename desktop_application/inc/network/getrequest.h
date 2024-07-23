#ifndef GETREQUEST_H
#define GETREQUEST_H

#include "networkcore.h"
#include "memory"

class GetRequest : public NetworkCore
{
    Q_OBJECT
public:
    GetRequest(HttpManager *parent = nullptr);
    void FetchMemberJsonData();

signals:
    void MemberJsonFetched(const std::unique_ptr<QJsonArray> &fetched_data);
    void TokenNotValid();

private slots:
    void OnFetchMemberJsonDataReplyRecieved();

private:
    QNetworkReply* GetHttpReply(const QNetworkRequest &request) override;
    HttpManager *parent_;
};

#endif // GETREQUEST_H
