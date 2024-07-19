#ifndef NETWORKCORE_H
#define NETWORKCORE_H

#include <QObject>
#include <QtNetwork>

#define API_ROOT_ADRESS "http://localhost:3000/api/"
#define API_LOGIN_ADRESS "login"
#define API_REGISTER_ADRESS "register"
#define API_FETCH_ADRESS "users"
#define API_PUSH_ADRESS "users"

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
    NetworkCore() = default;
    virtual QNetworkReply* GetHttpReply(const QNetworkRequest &request) = 0;
    template<typename T>
    void SendHttpRequest(const QString &api_adress,
                         const QString &token,
                         T* requester_object,
                         void (T::*slot_function)()){
        QUrl http_url(QString(API_ROOT_ADRESS) + api_adress);
        QNetworkRequest http_request(http_url);
        http_request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

        if(token.size())
            http_request.setRawHeader("Authorization", "Bearer " + token.toUtf8());

        qDebug() << "#### on http request, http headers ####";
        QList<QByteArray> headerList = http_request.rawHeaderList();
        for (const QByteArray &header : headerList) {
            qDebug() << header << ": " << http_request.rawHeader(header);
        }
        qDebug() << "#########################################";

        http_reply = GetHttpReply(http_request);
        connect(http_reply, &QNetworkReply::finished,
                requester_object, slot_function);
    }
    QJsonObject ReadBody();

    QNetworkAccessManager http_access_manager;
    QJsonDocument http_body_data;
    QNetworkReply *http_reply;
};

#endif // NETWORKCORE_H
