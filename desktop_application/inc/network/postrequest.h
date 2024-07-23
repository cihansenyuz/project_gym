#ifndef POSTREQUEST_H
#define POSTREQUEST_H

#include "networkcore.h"

class PostRequest : public NetworkCore
{
    Q_OBJECT
public:
    PostRequest(HttpManager *parent = nullptr);
    void LoginRequest(const QString &email, const QString password);
    void RegisterRequest(const QString &email, const QString password);
    void ReconnectRequest(const QString &password);
    HttpManager *parent_;
signals:
    void LoginAttempt(bool success);
    void RegisterAttempt(bool success);
    void ReconnectAttempt(bool success);
    void ConnectionToServer();

private slots:
    void OnRegisterReplyRecieved();
    void OnLoginReplyRecieved();
    void OnReconnectReplyRecieved();

private:
    QNetworkReply* GetHttpReply(const QNetworkRequest &request) override;

};

#endif // POSTREQUEST_H
