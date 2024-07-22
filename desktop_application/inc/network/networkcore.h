#ifndef NETWORKCORE_H
#define NETWORKCORE_H

#include <QObject>
#include <QtNetwork>

#define USE_LOCAL_HOST 1 // 0: local host, 1: google cloud

#if USE_LOCAL_HOST
#define API_ROOT_ADRESS "https://www.cangorkemgunes.com/api/"
#pragma message("gCloud end point is in use")
#else
#define API_ROOT_ADRESS "http://localhost:3000/api/"
#pragma message("local end point is in use")
#endif

#define API_LOGIN_ADRESS "login"
#define API_REGISTER_ADRESS "register"
#define API_FETCH_ADRESS "users"
#define API_PUSH_ADRESS "users"

#define FETCHED_FILE_PATH "../../members.json"

/*
 * implemented HTTP status codes in server side
 * for API_LOGIN_ADRESS
 *  POST request
 *      200 OK, email password match, returns token with code: UserFound
 *      400 Bad Request, no email or password, returns with code: BadRequest
 *      404 Not Found, email doesnot match, returns with code: NoUserFound
 *      404 Not Found, password doesnot match, returns with code: IncorrectPassword
 *
 * for API_REGISTER_ADRESS
 *  POST request
 *      201 Created
 *      400 Bad Request, returns with code: BadRequest
 *
 * for API_FETCH_ADRESS && API_PUSH_ADRESS
 *  GET request
 *      200 OK, token verified
 *      204 No Content, first time login
 *      401 Unauthorized, token verify failed
 *      403 Forbidden, no token given
 *  PUT request
 *      200 OK, token verified
 *      401 Unauthorized, token verify failed
 *      403 Forbidden, no token given
 * */

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
