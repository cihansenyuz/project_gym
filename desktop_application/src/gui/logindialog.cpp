#include "../../inc/gui/logindialog.h"
#include "../../ui/ui_logindialog.h"

LoginDialog::LoginDialog(HttpManager *http_manager, QWidget *parent)
    : http_manager_(http_manager), QDialog(parent)
    , ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
    ui->stacked_login_screens->setCurrentIndex(loginScreen);

    connect(ui->login_push_button, &QPushButton::clicked,
            this, &LoginDialog::OnLoginPushButtonClicked);
    connect(ui->register_push_button, &QPushButton::clicked,
            this, &LoginDialog::OnRegisterPushButtonClicked);
    connect(ui->create_push_button, &QPushButton::clicked,
            this, &LoginDialog::OnCreatePushButtonClicked);
    connect(ui->cancel_push_button, &QPushButton::clicked,
            this, &LoginDialog::OnCancelPushButtonClicked);

}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::OnLoginPushButtonClicked() {
    http_manager_->LoginRequest(ui->email_line_edit->text(),
                              ui->password_line_edit->text());
    connect(this->http_manager_, &HttpManager::LoginAttemptResult,
            this, &LoginDialog::OnLoginAttemptResult);
}

void LoginDialog::OnRegisterPushButtonClicked() {
    ui->stacked_login_screens->setCurrentIndex(registerScreen);
}

void LoginDialog::OnCancelPushButtonClicked() {
    ui->stacked_login_screens->setCurrentIndex(loginScreen);
}

void LoginDialog::OnCreatePushButtonClicked() {
    if (ui->email_register_line_edit->text() ==
            ui->confirm_email_register_line_edit->text() &&
        ui->password_register_line_edit->text() ==
            ui->confirm_password_register_line_edit->text()) {

        http_manager_->RegisterRequest(ui->email_register_line_edit->text(),
                                  ui->password_register_line_edit->text());

        ui->stacked_login_screens->setCurrentIndex(loginScreen);
    } else if (ui->email_register_line_edit->text() !=
               ui->confirm_email_register_line_edit->text()) {
        ui->confirm_password_label->clear();
        ui->confirm_email_label->setText("does not match!");
        return;
    } else if (ui->password_register_line_edit->text() !=
               ui->confirm_password_register_line_edit->text()) {
        ui->confirm_email_label->clear();
        ui->confirm_password_label->setText("does not match!");
        return;
    }
}

void LoginDialog::OnLoginAttemptResult(bool success){
    if(success)
        this->destroy();
    else
        ui->login_fail_message->setText("User is not registered or wrong password!");
}
