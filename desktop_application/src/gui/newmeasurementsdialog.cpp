#include "../../inc/gui/newmeasurementsdialog.h"
#include "../../ui/ui_newmeasurementsdialog.h"

NewMeasurementsDialog::NewMeasurementsDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::NewMeasurementsDialog)
{
    ui->setupUi(this);
    ui->taken_date_edit->setDate(QDate::currentDate());
    connect(ui->save_push_button, &QPushButton::clicked,
            this, &NewMeasurementsDialog::OnSaveButtonClicked);
}

NewMeasurementsDialog::~NewMeasurementsDialog()
{
    delete ui;
}

void NewMeasurementsDialog::OnSaveButtonClicked()
{
    Measurement new_measurement(ui->taken_date_edit->date(),
                                ui->weight_line_edit->text().toInt(),
                                ui->shoulder_line_edit->text().toInt(),
                                ui->chest_line_edit->text().toInt(),
                                ui->arm_line_edit->text().toInt(),
                                ui->belly_line_edit->text().toInt(),
                                ui->hip_line_edit->text().toInt(),
                                ui->leg_line_edit->text().toInt());

    emit NewMeasurements(new_measurement);
    close();
}

