#include "../../inc/network/postrequest.h"
#include "../../inc/network/httpmanager.h"

PostRequest::PostRequest(HttpManager *parent)
    : parent_(parent) {}

void PostRequest::LoginRequest(const QString &email, const QString password){
    QJsonObject user_info;
    user_info["email"] = email;
    user_info["password"] = password;
    http_body_data = QJsonDocument(user_info);
    SendHttpRequest(API_LOGIN_ADRESS, parent_->token, this, &PostRequest::OnLoginReplyRecieved);
    emit LoginRequestSent();
}

void PostRequest::RegisterRequest(const QString &email, const QString password){
    QJsonObject user_info;
    user_info["email"] = email;
    user_info["password"] = password;
    http_body_data = QJsonDocument(user_info);
    SendHttpRequest(API_REGISTER_ADRESS, parent_->token, this, &PostRequest::OnRegisterReplyRecieved);
}

void PostRequest::OnRegisterReplyRecieved(){
    if(http_reply->error() == QNetworkReply::NoError)
        ;
    else
        ;
}

void PostRequest::OnLoginReplyRecieved(){
    QJsonObject message;
    message = ReadBody();

    if(message["code"] == UserFound){
        parent_->token = message["Authorization"].toString();
        emit LoginAttempt(true);
    }
    else if (message["code"] == NoUserFound ||
             message["code"] == IncorrectPassword ||
             message["code"] == BadRequest)
        emit LoginAttempt(false);
    else
        qDebug() << "login error: " << http_reply->error();

    qDebug() << "#### on login(post) reply, http body fields ####";
    for(auto &key : message.keys())
        qDebug() << key << message[key];
    qDebug() << "#########################################";
}

QNetworkReply* PostRequest::GetHttpReply(const QNetworkRequest &request){
    qDebug() << "post request done";
    return http_access_manager.post(request, http_body_data.toJson());
}
