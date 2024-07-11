#include "../../inc/network/httpmanager.h"

HttpManager::HttpManager() {}

void HttpManager::PostHttpRequest(const QString &api_adress, RequestOption selection, void (HttpManager::*slot_function)()){
    QUrl http_url(QString(API_ROOT_ADRESS) + api_adress);
    QNetworkRequest http_request(http_url);
    http_request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    switch(selection){
    case Put:
        http_reply = http_acces_manager.put(http_request, QJsonDocument(user_info).toJson()); break;
    case Get:
        http_reply = http_acces_manager.get(http_request, QJsonDocument(user_info).toJson()); break;
    case Post:
        http_reply = http_acces_manager.post(http_request, QJsonDocument(user_info).toJson()); break;
    }

    http_reply = http_acces_manager.post(http_request, QJsonDocument(user_info).toJson());
    qDebug() << "http request posted";
    connect(http_reply, &QNetworkReply::finished,
            this, slot_function);
}

void HttpManager::LoginRequest(const QString &email, const QString password){
    user_info["email"] = email;
    user_info["password"] = password;
    PostHttpRequest(API_LOGIN_ADRESS, RequestOption::Post, &HttpManager::OnLoginReplyRecieved);
}

void HttpManager::RegisterRequest(const QString &email, const QString password){
    user_info["email"] = email;
    user_info["password"] = password;
    PostHttpRequest(API_REGISTER_ADRESS, RequestOption::Post, &HttpManager::OnRegisterReplyRecieved);
}

void HttpManager::OnRegisterReplyRecieved(){
    if(http_reply->error() == QNetworkReply::NoError)
        ;
    else
        ;
}

void HttpManager::OnLoginReplyRecieved(){
    qDebug() << "login reply recieved";
    if(http_reply->error() == QNetworkReply::NoError){

        QJsonObject message;
        message = ReadBody();
        if(message["code"] == UserFound)
            emit LoginAttempt(true);
        else
            emit LoginAttempt(false);
    }
    else
        qDebug() << "network error: " << http_reply->errorString();
}

void HttpManager::OnFetchMemberJsonDataReplyRecieved(){
    if(http_reply->error() == QNetworkReply::NoError){
        QByteArray reply = http_reply->readAll();
        QFile file(FETCHED_FILE_PATH);
        if (file.open(QIODevice::WriteOnly)) {
            file.write(reply.data());
            file.close();
            qDebug() << "JSON file created successfully.";
            emit MemberJsonFetched();
        } else {
            qDebug() << "Unable to open file for writing.";
        }
    }
    else
        ;
}

void HttpManager::FetchMemberJsonData(){
    PostHttpRequest("address_of_data", RequestOption::Get, &HttpManager::OnFetchMemberJsonDataReplyRecieved);
    emit http_reply->finished();
}

void HttpManager::PushMemberJsonData(){

}

QJsonObject HttpManager::ReadBody(){
    QByteArray raw_data = http_reply->readAll();
    QJsonDocument body_message_doc = QJsonDocument::fromJson(raw_data.data());
    return body_message_doc.object();
}
