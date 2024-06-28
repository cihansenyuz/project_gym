/**
  ******************************************************************************
  * @file    weeklyexerciseplan.hpp
  * @author  Cihan Senyuz
  * @date    27.06.2024
  * @brief   Header for weeklyexerciseplan.cpp file.
  *
  *             This file contains the definition of the WeeklyExercisePlan class,
  *         which represents a plan for exercises over a week. The class includes
  *         methods to add and manage daily exercise plans within the weekly plan,
  *         convert the plan to a JSON representation, and get the remaining days
  *         in the plan period.
  *
  ******************************************************************************
  */

#ifndef WEEKLYEXERCISEPLAN_H
#define WEEKLYEXERCISEPLAN_H

#include <vector>
#include <QJsonObject>
#include <QJsonArray>
#include <QDate>
#include "dailyexerciseplan.h"

class WeeklyExercisePlan
{
public:
    WeeklyExercisePlan() = default;
    WeeklyExercisePlan(const QDate &end_date, const QDate &start_date = QDate::currentDate());
    QJsonObject toJson() const;

    void AddNewDailyExercisePlan(const DailyExercisePlan &new_daily_plan);
    void ClearWeeklyExercisePlan();
    void SetWeeklyExercisePlan(const std::vector<DailyExercisePlan> &new_weekly_plan);
    void SetWeeklyExercisePlanPeriod(QDate start_date, QDate end_date);
    bool HasWeeklyExercisePlan() const;

    short GetRemainingDays();
    std::pair<QDate, QDate> GetWeeklyExercisePlanPeriod();
    std::vector<DailyExercisePlan> GetWeeklyExercisePlan();

private:
    std::vector<DailyExercisePlan> weekly_plan_;
    QDate start_date_;
    QDate end_date_;
};

#endif // WEEKLYEXERCISEPLAN_H
