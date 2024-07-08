#include "../../inc/network/httpmanager.h"

HttpManager::HttpManager() {}

void HttpManager::PostHttpRequest(const QString &api_adress){
    QUrl http_url(QString("https://www.cangorkemgunes.com/api/") + api_adress);
    QNetworkRequest http_request(http_url);
    http_request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    http_reply = http_manager.post(http_request, QJsonDocument(user_info).toJson());
    qDebug() << "http request posted";
    connect(http_reply, &QNetworkReply::finished,
            this, &HttpManager::OnHttpReplyRecieved);
}

void HttpManager::LoginRequest(const QString &email, const QString password){
    user_info["email"] = email;
    user_info["password"] = password;
    PostHttpRequest("login");
}

void HttpManager::RegisterRequest(const QString &email, const QString password){
    user_info["email"] = email;
    user_info["password"] = password;
    PostHttpRequest("register");
}

void HttpManager::OnHttpReplyRecieved(){
    qDebug() << "http request reply recieved";
    QByteArray raw_data(http_reply->readAll());
    qDebug() << raw_data.toStdString();

    if(http_reply->error() == QNetworkReply::NoError)
        emit LoginAttemptResult(true);
    else
        emit LoginAttemptResult(false);
}
