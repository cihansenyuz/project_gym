#ifndef PUTREQUEST_H
#define PUTREQUEST_H

#include "networkcore.h"

class PutRequest : public NetworkCore
{
    Q_OBJECT
public:
    PutRequest(HttpManager *parent = nullptr);
    void PushMemberJsonData(const QJsonArray* data_to_push);

private slots:
    void OnPushMemberJsonDataReplyRecieved();

private:
    QNetworkReply* GetHttpReply(const QNetworkRequest &request) override;
    HttpManager *parent_;
};

#endif // PUTREQUEST_H
