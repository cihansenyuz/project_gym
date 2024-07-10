#ifndef HTTPMANAGER_H
#define HTTPMANAGER_H

#include <QObject>
#include <QtNetwork>

// http reply codes
enum Code{
    BadRequest,
    UserFound,
    NoUserFound,
    IncorrectPassword
};

class HttpManager : public QObject
{
    Q_OBJECT
public:
    HttpManager();
    void LoginRequest(const QString &email, const QString password);
    void RegisterRequest(const QString &email, const QString password);
    void FetchMemberJsonData();

signals:
    void LoginAttempt(bool success);
    void MemberJsonFetched();

private slots:
    void OnRegisterReplyRecieved();
    void OnLoginReplyRecieved();
    void OnFetchMemberJsonDataReplyRecieved();

private:
    void PostHttpRequest(const QString &api_adress, void (HttpManager::*slot_function)());
    QJsonObject ReadBody();

    QNetworkAccessManager http_acces_manager;
    QNetworkReply *http_reply;
    QJsonObject user_info;
};

#endif // HTTPMANAGER_H
