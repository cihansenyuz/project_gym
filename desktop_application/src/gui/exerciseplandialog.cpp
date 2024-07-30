#include "../../inc/gui/exerciseplandialog.h"
#include "../../ui/ui_exerciseplandialog.h"

ExercisePlanDialog::ExercisePlanDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ExercisePlanDialog)
{
    ui->setupUi(this);
}

ExercisePlanDialog::~ExercisePlanDialog()
{
    delete ui;
}
