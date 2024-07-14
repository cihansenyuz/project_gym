#ifndef PUTREQUEST_H
#define PUTREQUEST_H

#include "networkcore.h"

class PutRequest : public NetworkCore
{
    Q_OBJECT
public:
    PutRequest();
    void PushMemberJsonData(const QJsonArray* data_to_push);

private slots:
    void OnPushMemberJsonDataReplyRecieved();

private:
    QNetworkReply* GetHttpReply(const QNetworkRequest &request) override;
};

#endif // PUTREQUEST_H
