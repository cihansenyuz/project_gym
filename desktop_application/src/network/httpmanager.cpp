#include "../../inc/network/httpmanager.h"

HttpManager::HttpManager() {}

void HttpManager::PostHttpRequest(const QString &api_adress, void (HttpManager::*slot_function)()){
    QUrl http_url(QString("https://www.cangorkemgunes.com/api/") + api_adress);
    QNetworkRequest http_request(http_url);
    http_request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    http_reply = http_manager.post(http_request, QJsonDocument(user_info).toJson());
    qDebug() << "http request posted";
    connect(http_reply, &QNetworkReply::finished,
            this, slot_function);
}

void HttpManager::LoginRequest(const QString &email, const QString password){
    user_info["email"] = email;
    user_info["password"] = password;
    PostHttpRequest("login", &HttpManager::OnLoginReplyRecieved);
}

void HttpManager::RegisterRequest(const QString &email, const QString password){
    user_info["email"] = email;
    user_info["password"] = password;
    PostHttpRequest("register", &HttpManager::OnRegisterReplyRecieved);
}

void HttpManager::OnRegisterReplyRecieved(){
    if(http_reply->error() == QNetworkReply::NoError)
        ;
    else
        ;
}

void HttpManager::OnLoginReplyRecieved(){
    qDebug() << "login reply recieved";
    if(http_reply->error() == QNetworkReply::NoError)
        emit LoginAttempt(true);
    else
        emit LoginAttempt(false);
}

void HttpManager::OnFetchMemberJsonDataReplyRecieved(){
    if(http_reply->error() == QNetworkReply::NoError){
        QByteArray raw_data = http_reply->readAll();
        QJsonDocument recieved_member_records = QJsonDocument::fromJson(raw_data.data());

        QFile file("../../members_fetched.json");
        if (file.open(QIODevice::WriteOnly)) {
            file.write(recieved_member_records.toJson(QJsonDocument::Indented)); // Indented format
            file.close();
            qDebug() << "JSON file created successfully.";
        } else {
            qDebug() << "Unable to open file for writing.";
        }
    }
    else
        ;
}

void HttpManager::FetchMemberJsonData(){
    PostHttpRequest("address_of_data", &HttpManager::OnFetchMemberJsonDataReplyRecieved);
}
