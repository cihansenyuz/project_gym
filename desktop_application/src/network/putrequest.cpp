#include "../../inc/network/putrequest.h"
#include "../../inc/network/httpmanager.h"

PutRequest::PutRequest(HttpManager *parent)
    : parent_(parent) {}

void PutRequest::OnPushMemberJsonDataReplyRecieved(){
    qDebug() << "#### on push data(put) reply ####";
    if(http_reply->error() == QNetworkReply::NoError){
        if(GetHttpStatusCode() == 200)
            qDebug() << "data uploaded to the cloud";
        else if(GetHttpStatusCode() == 401 || GetHttpStatusCode() == 403)
            qDebug() << "push failed, unauthorized attempt";
    }
    else
        qDebug() << "push error: " << http_reply->error();
}

void PutRequest::PushMemberJsonData(const QJsonArray* data_to_push){
    http_body_data = QJsonDocument(*data_to_push);
    SendHttpRequest(API_PUSH_ADDRESS, parent_->session_token, this, &PutRequest::OnPushMemberJsonDataReplyRecieved);
}

QNetworkReply* PutRequest::GetHttpReply(const QNetworkRequest &request){
    qDebug() << "put request done";
    return http_access_manager.put(request, http_body_data.toJson());
}
