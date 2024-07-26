/**
  ******************************************************************************
  * @file    dailyexerciseplan.hpp
  * @author  Cihan Senyuz
  * @date    27.06.2024
  * @brief   Header for dailyexerciseplan.cpp file.
  *
  *             This file contains the definition of the DailyExercisePlan class,
  *         which represents a plan for daily exercises. The class includes
  *         methods to add new exercises to the plan, convert the plan to a JSON
  *         representation, and get the cooldown period.
  *
  ******************************************************************************
  */

#ifndef DAILYEXERCISEPLAN_H
#define DAILYEXERCISEPLAN_H

#include <QJsonArray>
#include "exercise.h"

class DailyExercisePlan
{
public:
    DailyExercisePlan() = default;
    void AddNewExercise(Exercise *new_exercise);
    void SetCooldownPeriod(short days);
    void SetDailyExecisePlan(const std::vector<Exercise*> &new_plan);
    QJsonObject toJson() const;

    short GetCooldownPeriod() const;
    std::vector<Exercise*> GetDailyExercisePlan();

private:
    std::vector<Exercise*> daily_plan_;
    short cooldown_period_;
};

#endif // DAILYEXERCISEPLAN_H
