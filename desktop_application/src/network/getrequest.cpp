#include "../../inc/network/getrequest.h"
#include "../../inc/network/httpmanager.h"

GetRequest::GetRequest(HttpManager *parent)
    : parent_(parent) {}

/*void GetRequest::OnFetchMemberJsonDataReplyRecieved(){
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
}*/

void GetRequest::OnFetchMemberJsonDataReplyRecieved(){
    qDebug() << "#### on fetch(get) reply ####";
    if(http_reply->error() == QNetworkReply::NoError){
        QByteArray reply = http_reply->readAll();
        http_body_data = QJsonDocument::fromJson(reply.data());

        if(GetHttpStatusCode() == 200){
            emit MemberJsonFetched(new QJsonArray(http_body_data.array()));
            qDebug() << "member json array fetched successfully";
        }
        else if(GetHttpStatusCode() == 204 && http_body_data.isNull()) {
            emit MemberJsonFetched(new QJsonArray);
            qDebug() << "fetched successfully, first time login";
        }
        else if(GetHttpStatusCode() == 401 || GetHttpStatusCode() == 403)
            qDebug() << "fetch failed, unauthorized attempt";
        else if(http_body_data.isNull())
            qDebug() << "JSON array is null";
        else if(!http_body_data.isArray())
            qDebug() << "JSON is not an array.";
    }
    else
        qDebug() << "fetch error: " << http_reply->error();
    qDebug() << "#########################################\n";
}

void GetRequest::FetchMemberJsonData(){
    SendHttpRequest(API_FETCH_ADRESS, parent_->token, this, &GetRequest::OnFetchMemberJsonDataReplyRecieved);
}

QNetworkReply* GetRequest::GetHttpReply(const QNetworkRequest &request){
    qDebug() << "get request done";
    return http_access_manager.get(request, http_body_data.toJson());
}
