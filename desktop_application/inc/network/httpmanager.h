#ifndef HTTPMANAGER_H
#define HTTPMANAGER_H

#include <QObject>
#include <QtNetwork>

#define API_ROOT_ADRESS "https://www.cangorkemgunes.com/api/"
#define API_LOGIN_ADRESS "login"
#define API_REGISTER_ADRESS "register"
#define API_FETCH_ADRESS "users"
#define API_PUSH_ADRESS ""

#define FETCHED_FILE_PATH "../../members.json"

enum ReplyCode{
    BadRequest,
    UserFound,
    NoUserFound,
    IncorrectPassword
};

enum RequestOption{
    Put,
    Get,
    Post
};

class HttpManager : public QObject
{
    Q_OBJECT
public:
    HttpManager();
    void LoginRequest(const QString &email, const QString password);
    void RegisterRequest(const QString &email, const QString password);
    void FetchMemberJsonData();
    void PushMemberJsonData(const QJsonArray* data_to_push);

signals:
    void LoginAttempt(bool success);
    void MemberJsonFetched();

private slots:
    void OnRegisterReplyRecieved();
    void OnLoginReplyRecieved();
    void OnFetchMemberJsonDataReplyRecieved();
    void OnPushMemberJsonDataReplyRecieved();

private:
    void PostHttpRequest(const QString &api_adress, RequestOption selection, void (HttpManager::*slot_function)());
    QJsonObject ReadBody();

    QNetworkAccessManager http_acces_manager;
    QNetworkReply *http_reply;
    QJsonDocument http_body_data;
};

#endif // HTTPMANAGER_H
