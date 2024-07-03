/**
  ******************************************************************************
  * @file    cardioworkout.hpp
  * @author  Cihan Senyuz
  * @date    27.06.2024
  * @brief   Header for cardioworkout.cpp file.
  *
  *             This file contains the definition of the CardioWorkout class,
  *         which represents a specific type of exercise focusing on cardiovascular
  *         training. The class includes an additional attribute for the duration
  *         of the workout.
  *
  ******************************************************************************
  */

#ifndef CARDIOWORKOUT_H
#define CARDIOWORKOUT_H

#include "exercise.h"
#include <QJsonObject>

class CardioWorkout : public Exercise
{
public:
    CardioWorkout() = delete;
    CardioWorkout(ExerciseType type, ExerciseName name, short durition);
    QJsonObject toJson() const override;

    short GetDurition() const;

private:
    short durition_;
};

#endif // CARDIOWORKOUT_H
