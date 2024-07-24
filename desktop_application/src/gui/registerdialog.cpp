#include "../../inc/gui/registerdialog.h"
#include "../../ui/ui_registerdialog.h"

RegisterDialog::RegisterDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::RegisterDialog)
{
    ui->setupUi(this);
    ui->register_stacked_widget->setCurrentIndex(Info);

    connect(ui->next_push_button_info, &QPushButton::clicked,
            this, &RegisterDialog::OnNextButtonInfoClicked);
    connect(ui->next_push_button_sub, &QPushButton::clicked,
            this, &RegisterDialog::OnNextButtonSubClicked);
    connect(ui->save_push_button, &QPushButton::clicked,
            this, &RegisterDialog::OnSaveButtonClicked);
}

RegisterDialog::~RegisterDialog()
{
    delete ui;
}

void RegisterDialog::OnNextButtonInfoClicked()
{
    new_member_ = std::make_unique<Member>(ui->name_line_edit->text(),
                                          ui->age_line_edit->text().toInt());

    ui->register_stacked_widget->setCurrentIndex(Subscription);
}


void RegisterDialog::OnNextButtonSubClicked()
{
    new_member_->SetSubscriptionPeriod(ui->start_date_calender->selectedDate(),
                                      ui->end_date_calender->selectedDate());

    ui->register_stacked_widget->setCurrentIndex(Payment);
}


void RegisterDialog::OnSaveButtonClicked()
{
    // read inputs from the page

    emit MemberCreated(new_member_);
    close();
}

