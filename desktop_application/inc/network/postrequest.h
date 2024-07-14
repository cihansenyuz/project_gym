#ifndef POSTREQUEST_H
#define POSTREQUEST_H

#include "networkcore.h"

class PostRequest : public NetworkCore
{
    Q_OBJECT
public:
    PostRequest();
    void LoginRequest(const QString &email, const QString password);
    void RegisterRequest(const QString &email, const QString password);

signals:
    void LoginAttempt(bool success);
    void LoginRequestSent();

private slots:
    void OnRegisterReplyRecieved();
    void OnLoginReplyRecieved();
};

#endif // POSTREQUEST_H
