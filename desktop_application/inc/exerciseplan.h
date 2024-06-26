/**
  ******************************************************************************
  * @file    exerciseplan.hpp
  * @author  Cihan Senyuz
  * @date    24.06.2024
  * @brief   Header for exerciseplan.cpp file.
  *                 Represents a fitness exercise plan with details such as start
  *          and end dates, weekly exercise routines, including cooldown periods,
  *          repetitions, sets, and types. Provides methods for managing exercise
  *          plan data.
  *
  ******************************************************************************
  */

#ifndef EXERCISEPLAN_H
#define EXERCISEPLAN_H

#include <vector>
#include <QString>
#include <QDate>
#include <QDebug>
#include <QJsonObject>
#include <QJsonArray>
#include "exercise.h"

class ExercisePlan
{
public:
    ExercisePlan() = default;
    void AddNewExercise(const Exercise::Exercise &new_exercise);
    std::vector<Exercise::Exercise> GetWeeklyPlan() const;
    void SetTargetDate(const QDate &end_day, const QDate &start_day = QDate::currentDate());
    void SetWeeklyPlan(const std::vector<Exercise::Exercise> &weekly_plan);
    short RemaningDays();
    void PrintPlan();
    std::pair<QDate, QDate> GetExercisePeriod();
    void ClearExercisePlan();
    QJsonObject toJson() const;

private:
    std::vector<Exercise::Exercise> weekly_plan_;
    QDate start_day_;
    QDate end_day_;
};

#endif // EXERCISEPLAN_H
