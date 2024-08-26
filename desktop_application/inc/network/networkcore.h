/**
  ******************************************************************************
  * @file    networkcore.hpp
  * @author  Cihan Senyuz
  * @date    14.07.2024
  * @brief   Header for NetworkCore class.
  *          This file contains the definition of the NetworkCore class, which
  *          manages HTTP network communications. The class includes methods for
  *          sending HTTP requests and handling responses.
  *
  ******************************************************************************
  */

#ifndef NETWORKCORE_H
#define NETWORKCORE_H

#include <QObject>
#include <QtNetwork>

#ifndef HOST
    #define HOST "https://www.cangorkemgunes.com/api/"
#endif

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
    NetworkCore() = default;
    virtual QNetworkReply* GetHttpReply(const QNetworkRequest &request) = 0;
    template<typename T>
    void SendHttpRequest(const QString &api_address,
                         const QString &token,
                         T* requester_object,
                         void (T::*slot_function)()){
        QUrl http_url(QString(HOST) + api_address);
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
                requester_object, slot_function,
                Qt::SingleShotConnection);
    }
    QJsonObject ReadBody();
    int GetHttpStatusCode();

    QNetworkAccessManager http_access_manager;
    QJsonDocument http_body_data;
    QNetworkReply *http_reply;
};

#endif // NETWORKCORE_H
