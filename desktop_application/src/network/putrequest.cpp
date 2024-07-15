#include "../../inc/network/putrequest.h"
#include "../../inc/network/httpmanager.h"

PutRequest::PutRequest(HttpManager *parent)
    : parent_(parent) {}

void PutRequest::OnPushMemberJsonDataReplyRecieved(){
    if(http_reply->error() == QNetworkReply::NoError){
        qDebug() << "data uploaded to the cloud";
    }
    else
        qDebug() << "push error: " << http_reply->error();
}

void PutRequest::PushMemberJsonData(const QJsonArray* data_to_push){
    http_body_data = QJsonDocument(*data_to_push);
    SendHttpRequest(API_PUSH_ADRESS, parent_->token, this, &PutRequest::OnPushMemberJsonDataReplyRecieved);
}

QNetworkReply* PutRequest::GetHttpReply(const QNetworkRequest &request){
    qDebug() << "put request done";
    return http_access_manager.put(request, http_body_data.toJson());
}
