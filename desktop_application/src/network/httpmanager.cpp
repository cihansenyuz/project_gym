#include "../../inc/network/httpmanager.h"

HttpManager::HttpManager() {}

void HttpManager::PostHttpRequest(const QString &api_adress, RequestOption selection, void (HttpManager::*slot_function)()){
    QUrl http_url(QString(API_ROOT_ADRESS) + api_adress);
    QNetworkRequest http_request(http_url);
    http_request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    switch(selection){
        case Put:{
            http_reply = http_acces_manager.put(http_request, http_body_data.toJson());
            qDebug() << "put request done";
            break;
        }
        case Get:{
            http_reply = http_acces_manager.get(http_request);
            qDebug() << "get request done";
            break;
        }
        case Post:{
            http_reply = http_acces_manager.post(http_request, http_body_data.toJson());
            qDebug() << "post request done";
            break;
        }
    }

    connect(http_reply, &QNetworkReply::finished,
            this, slot_function);
}

void HttpManager::LoginRequest(const QString &email, const QString password){
    QJsonObject user_info;
    user_info["email"] = email;
    user_info["password"] = password;
    http_body_data = QJsonDocument(user_info);
    PostHttpRequest(API_LOGIN_ADRESS, RequestOption::Post, &HttpManager::OnLoginReplyRecieved);
}

void HttpManager::RegisterRequest(const QString &email, const QString password){
    QJsonObject user_info;
    user_info["email"] = email;
    user_info["password"] = password;
    http_body_data = QJsonDocument(user_info);
    PostHttpRequest(API_REGISTER_ADRESS, RequestOption::Post, &HttpManager::OnRegisterReplyRecieved);
}

void HttpManager::OnRegisterReplyRecieved(){
    if(http_reply->error() == QNetworkReply::NoError)
        ;
    else
        ;
}

void HttpManager::OnLoginReplyRecieved(){
    QJsonObject message;
    message = ReadBody();

    if(message["code"] == UserFound)
        emit LoginAttempt(true);
    else if (message["code"] == NoUserFound ||
             message["code"] == IncorrectPassword ||
             message["code"] == BadRequest)
        emit LoginAttempt(false);
    else
        qDebug() << "login error: " << http_reply->error();

    for(auto &key : message.keys())
        qDebug() << key << message[key];
}

void HttpManager::OnFetchMemberJsonDataReplyRecieved(){
    if(http_reply->error() == QNetworkReply::NoError){
        QByteArray reply = http_reply->readAll();
        QFile file(FETCHED_FILE_PATH);
        if (file.open(QIODevice::WriteOnly)) {
            file.write(reply.data());
            file.close();
            qDebug() << "JSON file fetched to local.";
            emit MemberJsonFetched();
        } else {
            qDebug() << "Unable to open file for writing.";
        }
    }
    else
        qDebug() << "fetch error: " << http_reply->error();
}

void HttpManager::OnPushMemberJsonDataReplyRecieved(){
    if(http_reply->error() == QNetworkReply::NoError){
        qDebug() << "data uploaded to the cloud";
    }
    else
        qDebug() << "push error: " << http_reply->error();
}

void HttpManager::FetchMemberJsonData(){
    PostHttpRequest(API_FETCH_ADRESS, RequestOption::Get, &HttpManager::OnFetchMemberJsonDataReplyRecieved);
}

void HttpManager::PushMemberJsonData(const QJsonArray* data_to_push){
    http_body_data = QJsonDocument(*data_to_push);
    PostHttpRequest(API_PUSH_ADRESS, RequestOption::Put, &HttpManager::OnPushMemberJsonDataReplyRecieved);
}

QJsonObject HttpManager::ReadBody(){
    QByteArray raw_data = http_reply->readAll();
    QJsonDocument body_message_doc = QJsonDocument::fromJson(raw_data.data());
    return body_message_doc.object();
}
