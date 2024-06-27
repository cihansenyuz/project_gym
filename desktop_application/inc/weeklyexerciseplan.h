#ifndef WEEKLYEXERCISEPLAN_H
#define WEEKLYEXERCISEPLAN_H

#include <vector>
#include <QJsonObject>
#include <QDate>
#include "dailyexerciseplan.h"

class WeeklyExercisePlan
{
public:
    WeeklyExercisePlan() = delete;
    WeeklyExercisePlan(const QDate &end_date, const QDate &start_date = QDate::currentDate());
    QJsonObject toJson() const;

    void AddNewDailyExercisePlan(const DailyExercisePlan &new_daily_plan);
    void ClearWeeklyExercisePlan();
    void SetWeeklyExercisePlan(const DailyExercisePlan &new_weekly_plan);

    short GetRemaningDays();
    std::pair<QDate, QDate> GetWeeklyExercisePlanPeriod();

private:
    std::vector<DailyExercisePlan> weekly_plan_;
    QDate start_date_;
    QDate end_date_;
};

#endif // WEEKLYEXERCISEPLAN_H
