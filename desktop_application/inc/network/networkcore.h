#ifndef NETWORKCORE_H
#define NETWORKCORE_H

#include <QObject>
#include <QtNetwork>

#define API_ROOT_ADRESS "https://www.cangorkemgunes.com/api/"
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

enum RequestOption{
    Put,
    Get,
    Post
};

class NetworkCore : public QObject
{
    Q_OBJECT
public:
    NetworkCore() = default;
    template<typename T>
    void PostHttpRequest(const QString &api_adress,
                         RequestOption selection,
                         T* requester_object,
                         void (T::*slot_function)()){
        QUrl http_url(QString(API_ROOT_ADRESS) + api_adress);
        QNetworkRequest http_request(http_url);
        http_request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
        if(token.size())
            http_request.setRawHeader("Authorization", "Bearer " + token.toUtf8());

        switch(selection){
        case Put:{
            http_reply = http_access_manager.put(http_request, http_body_data.toJson());
            qDebug() << "put request done";
            break;
        }
        case Get:{
            http_reply = http_access_manager.get(http_request);
            qDebug() << "get request done";
            break;
        }
        case Post:{
            http_reply = http_access_manager.post(http_request, http_body_data.toJson());
            qDebug() << "post request done";
            break;
        }
        }

        connect(http_reply, &QNetworkReply::finished,
                requester_object, slot_function);
    }
    QJsonObject ReadBody();

    QJsonDocument http_body_data;
    QNetworkReply *http_reply;
    QString token{""};

private:
    QNetworkAccessManager http_access_manager;
};

#endif // NETWORKCORE_H
