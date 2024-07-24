#include "../../inc/gui/newmeasurementsdialog.h"
#include "../../ui/ui_newmeasurementsdialog.h"

NewMeasurementsDialog::NewMeasurementsDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::NewMeasurementsDialog)
{
    ui->setupUi(this);
}

NewMeasurementsDialog::~NewMeasurementsDialog()
{
    delete ui;
}
