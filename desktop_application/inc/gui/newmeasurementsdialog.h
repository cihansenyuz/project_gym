#ifndef NEWMEASUREMENTSDIALOG_H
#define NEWMEASUREMENTSDIALOG_H

#include <QDialog>
#include "../member/measurement.h"

namespace Ui {
class NewMeasurementsDialog;
}

class NewMeasurementsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewMeasurementsDialog(QWidget *parent = nullptr);
    ~NewMeasurementsDialog();

signals:
    void NewMeasurements(const Measurement &new_measurements);

private slots:
    void OnSaveButtonClicked();

private:
    Ui::NewMeasurementsDialog *ui;
};

#endif // NEWMEASUREMENTSDIALOG_H
