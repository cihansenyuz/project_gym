#include "../../inc/network/getrequest.h"

GetRequest::GetRequest() {}

void GetRequest::OnFetchMemberJsonDataReplyRecieved(){
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

void GetRequest::FetchMemberJsonData(){
    PostHttpRequest(API_FETCH_ADRESS, RequestOption::Get,
                    this, &GetRequest::OnFetchMemberJsonDataReplyRecieved);
}
