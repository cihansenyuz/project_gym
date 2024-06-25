/**
  ******************************************************************************
  * @file    exerciseplan.hpp
  * @author  Cihan Senyuz
  * @date    24.06.2024
  * @brief   Header for exerciseplan.cpp file.
  *                 This file contains the class to manage exercise plan. Depends
  *          on the exercise.h header.
  *
  ******************************************************************************
  */

#ifndef EXERCISEPLAN_H
#define EXERCISEPLAN_H

#include <map>
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
    void AddNewExercise(const Exercise::Exercise_t &new_exercise, short cooldown_days);
    std::map<QString, Exercise::Exercise_t> GetWeeklyPlan() const;
    void SetTargetDate(const QDate &end_day, const QDate &start_day = QDate::currentDate());
    void SetWeeklyPlan(const std::map<QString, Exercise::Exercise_t> &weekly_plan);
    short RemaningDays();
    void PrintPlan();
    std::pair<QDate, QDate> GetExercisePeriod();
    void ClearExercisePlan();
    QJsonObject toJson() const;

private:
    std::map<QString, Exercise::Exercise_t> weekly_plan_;
    QDate start_day_;
    QDate end_day_;
};

#endif // EXERCISEPLAN_H
