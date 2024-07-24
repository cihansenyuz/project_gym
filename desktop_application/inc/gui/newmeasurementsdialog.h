#ifndef NEWMEASUREMENTSDIALOG_H
#define NEWMEASUREMENTSDIALOG_H

#include <QDialog>

namespace Ui {
class NewMeasurementsDialog;
}

class NewMeasurementsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewMeasurementsDialog(QWidget *parent = nullptr);
    ~NewMeasurementsDialog();

private:
    Ui::NewMeasurementsDialog *ui;
};

#endif // NEWMEASUREMENTSDIALOG_H
