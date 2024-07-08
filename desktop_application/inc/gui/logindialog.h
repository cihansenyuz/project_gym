#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include <QtNetwork>
#include <QJsonObject>

enum Screen{
    loginScreen,
    registerScreen
};

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = nullptr);
    ~LoginDialog();

private slots:
    void OnLoginPushButtonClicked();
    void OnRegisterPushButtonClicked();
    void OnCancelPushButtonClicked();
    void OnCreatePushButtonClicked();
    void OnHttpReplyRecieved();

private:
    void PostHttpRequest(const QJsonObject &user_info);

    Ui::LoginDialog *ui;
    QUrl http_url{QString("https://www.cangorkemgunes.com/api/login")};
    QNetworkRequest http_request{http_url};
    QNetworkAccessManager http_manager;
    QNetworkReply *http_reply;
    QJsonObject user_info;
};

#endif // LOGINDIALOG_H
