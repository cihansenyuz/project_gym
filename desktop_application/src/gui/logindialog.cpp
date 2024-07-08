#include "../../inc/gui/logindialog.h"
#include "../../ui/ui_logindialog.h"

LoginDialog::LoginDialog(QWidget *parent)
    : QDialog(parent)
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
    user_info["email"] = ui->email_line_edit->text();
    user_info["password"] = ui->password_line_edit->text();
    user_info["register"] = false;
    PostHttpRequest(user_info);
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

        user_info["email"] = ui->email_register_line_edit->text();
        user_info["password"] = ui->password_register_line_edit->text();
        user_info["register"] = true;
        PostHttpRequest(user_info);

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

void LoginDialog::PostHttpRequest(const QJsonObject &user_info){
    http_request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    http_reply = http_manager.post(http_request, QJsonDocument(user_info).toJson());
    qDebug() << "http request posted";
    connect(http_reply, &QNetworkReply::finished,
            this, &LoginDialog::OnHttpReplyRecieved);
}

void LoginDialog::OnHttpReplyRecieved(){
    /////////////////////
    // check http reply here
    /////////////////////
    qDebug() << "http request reply recieved";
    QByteArray raw_data(http_reply->readAll());
    qDebug() << raw_data.toStdString();
}
