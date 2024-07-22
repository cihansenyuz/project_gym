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

    connect(this->http_manager_, &PostRequest::LoginAttempt,
            this, &LoginDialog::OnLoginAttempt);
}

LoginDialog::~LoginDialog(){
    delete ui;
}

void LoginDialog::OnLoginPushButtonClicked() {
    http_manager_->LoginRequest(ui->email_line_edit->text(),
                              ui->password_line_edit->text());
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

void LoginDialog::OnLoginAttempt(bool success){
    if(login_fail_message){
        login_fail_message->close();
        login_fail_message.reset(nullptr);
    }

    if(success)
        this->destroy();
    else
        login_fail_message = std::make_unique<InfoDialog>("Invalid email or wrong password!", "Login Error");
}
