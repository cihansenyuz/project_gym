#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include <memory>
#include "../network/httpmanager.h"
#include "../gui/infodialog.h"

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
    explicit LoginDialog(HttpManager *http_manager, QWidget *parent = nullptr);
    ~LoginDialog();

private slots:
    void OnLoginPushButtonClicked();
    void OnRegisterPushButtonClicked();
    void OnCancelPushButtonClicked();
    void OnCreatePushButtonClicked();
    void OnLoginAttempt(bool success);

private:
    Ui::LoginDialog *ui;
    HttpManager *http_manager_;
    std::unique_ptr<InfoDialog> login_fail_message;
    std::mutex info_dialog_mutex;
};

#endif // LOGINDIALOG_H
