#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include "../network/httpmanager.h"
#include "../gui/infodialog.h"
#include <mutex>
#include <condition_variable>

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
    InfoDialog *dialog{nullptr};

    std::mutex status_mutex;
    std::condition_variable status_info_created;
};

#endif // LOGINDIALOG_H
