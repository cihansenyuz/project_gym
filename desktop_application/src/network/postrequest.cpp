#include "../../inc/network/postrequest.h"
#include "../../inc/network/httpmanager.h"

PostRequest::PostRequest(HttpManager *parent)
    : parent_(parent), NetworkCore(this) {}

void PostRequest::LoginRequest(const QString &email, const QString password){
    QJsonObject user_info;
    user_info["email"] = email;
    user_info["password"] = password;
    http_body_data = QJsonDocument(user_info);
    parent_->session_email = email;
    emit ConnectionToServer();
    SendHttpRequest(API_LOGIN_ADDRESS, parent_->session_token, this, &PostRequest::OnLoginReplyRecieved);
}

void PostRequest::RegisterRequest(const QString &email, const QString password){
    QJsonObject user_info;
    user_info["email"] = email;
    user_info["password"] = password;
    http_body_data = QJsonDocument(user_info);
    emit ConnectionToServer();
    SendHttpRequest(API_REGISTER_ADDRESS, parent_->session_token, this, &PostRequest::OnRegisterReplyRecieved);
}

void PostRequest::ReconnectRequest(const QString &password){
    QJsonObject user_info;
    user_info["email"] = "admin";
    user_info["password"] = password;
    http_body_data = QJsonDocument(user_info);
    parent_->session_token = "";
    qDebug() << "debug reconnect send";
    SendHttpRequest(API_LOGIN_ADDRESS, parent_->session_token, this, &PostRequest::OnReconnectReplyRecieved);
}

void PostRequest::OnRegisterReplyRecieved(){
    if(GetHttpStatusCode() == 201)
        emit RegisterAttempt(true);
    else{
        emit RegisterAttempt(false);
        qDebug() << "register error: " << http_reply->error();
    }
}

void PostRequest::OnLoginReplyRecieved(){
    QJsonObject message;
    message = ReadBody();

    if(GetHttpStatusCode() == 200 && message["code"] == UserFound){
        parent_->session_token = message["Authorization"].toString();
        emit LoginAttempt(true);
    }
    else if (GetHttpStatusCode() == 404){
        emit LoginAttempt(false);
    }
    else
        qDebug() << "login error: " << http_reply->error();

    qDebug() << "#### on login(post) reply, http body fields ####";
    for(auto &key : message.keys())
        qDebug() << key << message[key];
    qDebug() << "#########################################\n";
}

void PostRequest::OnReconnectReplyRecieved(){
    qDebug() << "debug reconnect reply";
    QJsonObject message;
    message = ReadBody();

    if(GetHttpStatusCode() == 200 && message["code"] == UserFound){
        parent_->session_token = message["Authorization"].toString();
        emit ReconnectAttempt(true);
    }
    else if (GetHttpStatusCode() == 404){
        emit ReconnectAttempt(false);
    }
    else
        qDebug() << "reconnect error: " << http_reply->error();

    qDebug() << "#### on reconnect(post) reply, http body fields ####";
    for(auto &key : message.keys())
        qDebug() << key << message[key];
    qDebug() << "#########################################\n";
}

QNetworkReply* PostRequest::GetHttpReply(const QNetworkRequest &request){
    qDebug() << "post request done";
    return http_access_manager.post(request, http_body_data.toJson());
}
