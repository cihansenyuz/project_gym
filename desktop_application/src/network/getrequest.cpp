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
        std::unique_ptr<QJsonArray> fetched_data;

        if(GetHttpStatusCode() == 200){
            fetched_data = std::make_unique<QJsonArray>(http_body_data.array());
            emit MemberJsonFetched(fetched_data);
            qDebug() << "member json array fetched successfully";
        }
        else if(GetHttpStatusCode() == 204 && http_body_data.isNull()) {
            fetched_data = std::make_unique<QJsonArray>();
            emit MemberJsonFetched(fetched_data);
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
    SendHttpRequest(API_FETCH_ADDRESS, parent_->token, this, &GetRequest::OnFetchMemberJsonDataReplyRecieved);
}

QNetworkReply* GetRequest::GetHttpReply(const QNetworkRequest &request){
    qDebug() << "get request done";
    return http_access_manager.get(request, http_body_data.toJson());
}
