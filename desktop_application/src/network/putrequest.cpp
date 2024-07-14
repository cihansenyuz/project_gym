#include "../../inc/network/putrequest.h"

PutRequest::PutRequest() {}

void PutRequest::OnPushMemberJsonDataReplyRecieved(){
    if(http_reply->error() == QNetworkReply::NoError){
        qDebug() << "data uploaded to the cloud";
    }
    else
        qDebug() << "push error: " << http_reply->error();
}

void PutRequest::PushMemberJsonData(const QJsonArray* data_to_push){
    http_body_data = QJsonDocument(*data_to_push);
    PostHttpRequest(API_PUSH_ADRESS, RequestOption::Put,
                    this, &PutRequest::OnPushMemberJsonDataReplyRecieved);
}
