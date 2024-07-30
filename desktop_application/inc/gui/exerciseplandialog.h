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
    void NewWeeklyPlanReady(const std::vector<DailyExercisePlan> &new_weekly_exercise_plan,
                            const QDate &start, const QDate &end);

private slots:
    void OnAddButtonClicked();
    void OnRemoveButtonClicked();
    void OnSaveDailyButtonClicked();
    void OnAddDailyButtonClicked();
    void OnApplyButtonClicked();
    void OnCancelButtonClicked();

private:
    Ui::ExercisePlanDialog *ui;
    DailyExercisePlan new_daily_plan;
    std::unique_ptr<ExerciseWeekView> exercise_day_tabs;
    std::vector<DailyExercisePlan> new_weekly_exercise_plan;
    int current_day{0};
};

#endif // EXERCISEPLANDIALOG_H
