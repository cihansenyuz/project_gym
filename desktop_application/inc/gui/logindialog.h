#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include "../network/httpmanager.h"

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
    void OnLoginAttemptResult(bool success);

private:
    Ui::LoginDialog *ui;
    HttpManager http_manager;
};

#endif // LOGINDIALOG_H
