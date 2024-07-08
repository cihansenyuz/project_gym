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
    void PostHttpRequest(const QString &api_adress);

    Ui::LoginDialog *ui;
    QNetworkAccessManager http_manager;
    QNetworkReply *http_reply;
    QJsonObject user_info;
};

#endif // LOGINDIALOG_H
