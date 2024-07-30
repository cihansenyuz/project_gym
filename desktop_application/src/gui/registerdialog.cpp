#include "../../inc/gui/registerdialog.h"
#include "../../ui/ui_registerdialog.h"

RegisterDialog::RegisterDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::RegisterDialog)
{
    ui->setupUi(this);
    ui->register_stacked_widget->setCurrentIndex(InfoPage);

    connect(ui->next_push_button_info, &QPushButton::clicked,
            this, &RegisterDialog::OnNextButtonInfoClicked);
    connect(ui->next_push_button_sub, &QPushButton::clicked,
            this, &RegisterDialog::OnNextButtonSubClicked);
    connect(ui->save_push_button, &QPushButton::clicked,
            this, &RegisterDialog::OnSaveButtonClicked);
    connect(ui->installments_spin_box, &QSpinBox::valueChanged,
            this, &RegisterDialog::OnInstallmentsValueChanged);

    radio_button_group = std::make_unique<QButtonGroup>(this);
    radio_button_group->addButton(ui->radio_button_1, 1);
    radio_button_group->addButton(ui->radio_button_3, 3);
    radio_button_group->addButton(ui->radio_button_6, 6);
    radio_button_group->addButton(ui->radio_button_12, 12);
}

RegisterDialog::~RegisterDialog()
{
    delete ui;
}

void RegisterDialog::OnNextButtonInfoClicked()
{
    new_member_ = std::make_unique<Member>(ui->name_line_edit->text(),
                                          ui->age_line_edit->text().toInt());

    ui->register_stacked_widget->setCurrentIndex(SubscriptionPage);
}


void RegisterDialog::OnNextButtonSubClicked()
{
    int period = radio_button_group->id(radio_button_group->checkedButton());
    new_member_->SetSubscriptionPeriod(ui->start_date_calender->selectedDate(),
                                      ui->start_date_calender->selectedDate().addMonths(period));

    ui->register_stacked_widget->setCurrentIndex(PaymentPage);
}


void RegisterDialog::OnSaveButtonClicked()
{
    PaymentPlan plan(ui->price_line_edit->text().toInt(),
                     ui->installments_spin_box->value(),
                     new_member_->GetSubscriptionStartDate());

    new_member_->SetPaymentPlan(plan);
    emit MemberCreated(new_member_);
    close();
}

void RegisterDialog::OnInstallmentsValueChanged(const int installment_quantity){
    float monthly_payment = ui->price_line_edit->text().toInt() / installment_quantity;
    ui->payment_label->setText(QString::number(monthly_payment));
}
