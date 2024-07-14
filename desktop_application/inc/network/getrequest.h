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
};

#endif // GETREQUEST_H
