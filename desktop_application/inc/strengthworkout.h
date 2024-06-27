/**
  ******************************************************************************
  * @file    strengthworkout.hpp
  * @author  Cihan Senyuz
  * @date    27.06.2024
  * @brief   Header for strengthworkout.cpp file.
  *
  *             This file contains the definition of the StrengthWorkout class,
  *         which represents a specific type of exercise focusing on strength
  *         training. The class includes additional attributes such as the
  *         number of sets and repetitions for the workout.
  *
  ******************************************************************************
  */

#ifndef STRENGTHWORKOUT_H
#define STRENGTHWORKOUT_H

#include "exercise.h"
#include <QJsonObject>

class StrengthWorkout : public Exercise
{
public:
    StrengthWorkout() = delete;
    StrengthWorkout(ExerciseType type, ExerciseName name, short set, short repeat);
    QJsonObject toJson() const override;

    short GetSet() const;
    short GetRepeat() const;

private:
    short set_;
    short repeat_;
};

#endif // STRENGTHWORKOUT_H
