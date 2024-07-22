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
    explicit LoginDialog(std::shared_ptr<HttpManager> &http_manager,
                         QWidget *parent = nullptr);
    ~LoginDialog();

private slots:
    void OnLoginPushButtonClicked();
    void OnRegisterPushButtonClicked();
    void OnCancelPushButtonClicked();
    void OnCreatePushButtonClicked();
    void OnLoginAttempt(bool success);

private:
    Ui::LoginDialog *ui;
    std::shared_ptr<HttpManager> http_manager_;
    std::unique_ptr<InfoDialog> action_message;
    std::mutex info_dialog_mutex;
};

#endif // LOGINDIALOG_H
