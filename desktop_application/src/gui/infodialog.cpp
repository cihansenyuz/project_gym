#include "../../inc/gui/infodialog.h"
#include "../../ui/ui_infodialog.h"

InfoDialog::InfoDialog(const QString &message, const QString &title, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::InfoDialog)
{
    ui->setupUi(this);
    ui->message_label->setWindowTitle(title);
    ui->message_label->setText(message);

    connect(ui->ok_button, &QPushButton::clicked,
            this, &InfoDialog::OnOkButtonClicked);
}

InfoDialog::~InfoDialog()
{
    delete ui;
}

void InfoDialog::OnOkButtonClicked(){
    this->destroy();
}
