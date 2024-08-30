#include "../../inc/network/deleterequest.h"
#include "../../inc/network/httpmanager.h"

DeleteRequest::DeleteRequest(HttpManager *parent)
    : parent_(parent) {}

void DeleteRequest::OnDeleteMemberReplyRecieved(){
    qDebug() << "#### on delete member(DELETE) reply ####";
    if(http_reply->error() == QNetworkReply::NoError){
        if(GetHttpStatusCode() == 200)
            qDebug() << "member deleted on the cloud";
        else if(GetHttpStatusCode() == 401 || GetHttpStatusCode() == 403)
            qDebug() << "delete failed, unauthorized attempt";
    }
    else
        qDebug() << "delete error: " << http_reply->error();
}

void DeleteRequest::DeleteMember(const QString &id){
    http_body_data = QJsonDocument(QJsonObject{
                                        {"id", id}
                                    });
    SendHttpRequest(API_PUSH_ADDRESS, parent_->token, this, &DeleteRequest::OnDeleteMemberReplyRecieved);
}

QNetworkReply* DeleteRequest::GetHttpReply(const QNetworkRequest &request){
    qDebug() << "put request done";
    return http_access_manager.put(request, http_body_data.toJson());
}
