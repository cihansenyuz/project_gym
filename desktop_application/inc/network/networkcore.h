#ifndef NETWORKCORE_H
#define NETWORKCORE_H

#include <QObject>
#include <QtNetwork>

#define DEV_MODE_USE_LOCAL_HOST 1 // 1: local host, 0: google cloud

#if DEV_MODE_USE_LOCAL_HOST
#define API_ROOT_ADDRESS "http://localhost:3000/api/"
#else
#define API_ROOT_ADDRESS "https://www.cangorkemgunes.com/api/"
#endif // DEV_MODE_USE_LOCAL_HOST

#define API_LOGIN_ADDRESS "login"
#define API_REGISTER_ADDRESS "register"
#define API_FETCH_ADDRESS "users"
#define API_PUSH_ADDRESS "users"

#define FETCHED_FILE_PATH "../../members.json"

enum ReplyCode{
    BadRequest,
    UserFound,
    NoUserFound,
    IncorrectPassword
};

class HttpManager;

class NetworkCore : public QObject
{
    Q_OBJECT
public:
    NetworkCore(HttpManager *parent = nullptr) : parent_(parent) {}
    virtual QNetworkReply* GetHttpReply(const QNetworkRequest &request) = 0;
    template<typename T>
    void SendHttpRequest(const QString &api_address,
                         const QString &token,
                         T* requester_object,
                         void (T::*slot_function)());
    QJsonObject ReadBody();
    int GetHttpStatusCode();

    QNetworkAccessManager http_access_manager;
    QJsonDocument http_body_data;
    QNetworkReply *http_reply;
    HttpManager *parent_;
};

#endif // NETWORKCORE_H
