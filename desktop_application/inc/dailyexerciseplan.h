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

#include <vector>
#include <QJsonObject>
#include "exercise.h"

class DailyExercisePlan
{
public:
    DailyExercisePlan() = default;
    void AddNewExercise(const Exercise &new_exercise);
    QJsonObject toJson() const;

    void GetCooldownPeriod() const;

private:
    std::vector<Exercise> daily_plan_;
    short cooldown_period_;
};

#endif // DAILYEXERCISEPLAN_H
