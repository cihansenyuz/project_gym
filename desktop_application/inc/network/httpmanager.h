#ifndef HTTPMANAGER_H
#define HTTPMANAGER_H

#include <QObject>
#include <QtNetwork>

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

private slots:
    void OnRegisterReplyRecieved();
    void OnLoginReplyRecieved();
    void OnFetchMemberJsonDataReplyRecieved();

private:
    void PostHttpRequest(const QString &api_adress, void (HttpManager::*slot_function)());

    QNetworkAccessManager http_manager;
    QNetworkReply *http_reply;
    QJsonObject user_info;
};

#endif // HTTPMANAGER_H
