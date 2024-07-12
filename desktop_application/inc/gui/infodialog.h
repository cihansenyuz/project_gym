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
