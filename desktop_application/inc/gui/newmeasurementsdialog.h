/**
  ******************************************************************************
  * @file    newmeasurementsdialog.hpp
  * @author  Cihan Senyuz
  * @date    24.07.2024
  * @brief   Header for NewMeasurementsDialog class.
  *          This file contains the definition of the NewMeasurementsDialog class,
  *          which represents a dialog for inputting new measurements. The class
  *          includes a signal for notifying when new measurements are saved and
  *          methods for handling user interactions.
  *
  ******************************************************************************
  */

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
