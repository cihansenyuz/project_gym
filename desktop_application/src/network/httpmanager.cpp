#include "../../inc/network/httpmanager.h"


QJsonArray* HttpManager::GetFetchedMemberJsonArray(){
    QJsonArray *fetched_array = new QJsonArray(GetRequest::http_body_data.array());
    return fetched_array;
}
