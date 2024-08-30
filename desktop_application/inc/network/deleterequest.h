#ifndef DELETEREQUEST_H
#define DELETEREQUEST_H

#include "networkcore.h"

class DeleteRequest : public NetworkCore
{
    Q_OBJECT
public:
    DeleteRequest(HttpManager *parent = nullptr);
    void DeleteMember(const QString &id);

private slots:
    void OnDeleteMemberReplyRecieved();

private:
    QNetworkReply* GetHttpReply(const QNetworkRequest &request) override;
    HttpManager *parent_;
};

#endif // DELETEREQUEST_H
