#include "../../inc/network/networkcore.h"

QJsonObject NetworkCore::ReadBody(){
    QByteArray raw_data = http_reply->readAll();
    QJsonDocument body_message_doc = QJsonDocument::fromJson(raw_data.data());
    return body_message_doc.object();
}
int NetworkCore::GetHttpStatusCode(){
    return http_reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
}
template<typename T>
void NetworkCore::SendHttpRequest(const QString &api_address,
                     const QString &token,
                     T* requester_object,
                     void (T::*slot_function)()){
    QUrl http_url(QString(API_ROOT_ADDRESS) + api_address);
    QNetworkRequest http_request(http_url);
    http_request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    if(token.size())
        http_request.setRawHeader("Authorization", "Bearer " + token.toUtf8());

    qDebug() << "#### on http request, http headers ####";
    QList<QByteArray> headerList = http_request.rawHeaderList();
    for (const QByteArray &header : headerList) {
        qDebug() << header << ": " << http_request.rawHeader(header);
    }
    qDebug() << "#########################################";
    std::lock_guard<std::mutex> lock(parent_->parent_->http_request_mutex);
    http_reply = GetHttpReply(http_request);
    connect(http_reply, &QNetworkReply::finished,
            requester_object, slot_function,
            Qt::SingleShotConnection);
}
