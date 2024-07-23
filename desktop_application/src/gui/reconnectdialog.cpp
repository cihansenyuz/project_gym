#include "../../inc/gui/reconnectdialog.h"
#include "../../ui/ui_reconnectdialog.h"

ReconnectDialog::ReconnectDialog(const QString &message, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ReconnectDialog)
{
    ui->setupUi(this);
    ui->message_label->setText(message);

    connect(ui->reconnect_push_button, &QPushButton::clicked,
            this, &ReconnectDialog::OnReconnectButtonClicked);

    this->show();
}

ReconnectDialog::~ReconnectDialog()
{
    qDebug() << "reconnect died";
    delete ui;
}

void ReconnectDialog::OnReconnectButtonClicked()
{
    emit Reconnect(ui->password_line_edit->text());
    this->close();
    //this->destroy();
}

