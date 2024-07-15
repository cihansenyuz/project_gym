#include "../../inc/network/httpmanager.h"

HttpManager::HttpManager()
    : PostRequest(this), GetRequest(this), PutRequest(this) {}
