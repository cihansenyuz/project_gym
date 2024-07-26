/**
  ******************************************************************************
  * @file    infodialog.hpp
  * @author  Cihan Senyuz
  * @date    12.07.2024
  * @brief   Header for InfoDialog class.
  *          This file contains the definition of the InfoDialog class, which
  *          represents a dialog for displaying informational messages to the user.
  *          The class includes methods for initializing the dialog with a message
  *          and title, and handling the OK button click event.
  *
  ******************************************************************************
  */

#ifndef INFODIALOG_H
#define INFODIALOG_H

#include <QDialog>

namespace Ui {
class InfoDialog;
}

class InfoDialog : public QDialog
{
    Q_OBJECT

public:
    explicit InfoDialog(const QString &message,
                        const QString &title = "",
                        QWidget *parent = nullptr);
    ~InfoDialog();

private slots:
    void OnOkButtonClicked();

private:
    Ui::InfoDialog *ui;
};

#endif // INFODIALOG_H
