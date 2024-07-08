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

signals:
    void LoginAttempt(bool success);

private slots:
    void OnHttpReplyRecieved();

private:
    void PostHttpRequest(const QString &api_adress);

    QNetworkAccessManager http_manager;
    QNetworkReply *http_reply;
    QJsonObject user_info;
};

#endif // HTTPMANAGER_H
