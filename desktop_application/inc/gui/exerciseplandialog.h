#ifndef EXERCISEPLANDIALOG_H
#define EXERCISEPLANDIALOG_H

#include <QDialog>
#include "../gui/components/exerciseweekview.h"

namespace Ui {
class ExercisePlanDialog;
}

class ExercisePlanDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ExercisePlanDialog(const std::vector<DailyExercisePlan> &old_weekly_exercise_plan,
                                QWidget *parent = nullptr);
    ~ExercisePlanDialog();
    void FillExercisePlanTable();
    void DeleteExercisePlanTable();

signals:
    void NewWeeklyPlanReady(std::vector<DailyExercisePlan> new_weekly_exercise_plan);

private slots:
    void OnAddButtonClicked();
    void OnRemoveButtonClicked();
    void OnApplyButtonClicked();
    void OnCancelButtonClicked();

private:
    Ui::ExercisePlanDialog *ui;
    std::unique_ptr<ExerciseWeekView> exercise_day_tabs;
    std::vector<DailyExercisePlan> new_weekly_exercise_plan;
};

#endif // EXERCISEPLANDIALOG_H
