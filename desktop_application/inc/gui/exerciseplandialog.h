#ifndef EXERCISEPLANDIALOG_H
#define EXERCISEPLANDIALOG_H

#include <QDialog>

namespace Ui {
class ExercisePlanDialog;
}

class ExercisePlanDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ExercisePlanDialog(QWidget *parent = nullptr);
    ~ExercisePlanDialog();

private:
    Ui::ExercisePlanDialog *ui;
};

#endif // EXERCISEPLANDIALOG_H
