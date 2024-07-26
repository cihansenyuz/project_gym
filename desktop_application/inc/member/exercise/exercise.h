/**
  ******************************************************************************
  * @file    exercise.hpp
  * @author  Cihan Senyuz
  * @date    24.06.2024
  * @brief   Header for exercise.cpp file.
  *                 This file contains the definition of the Exercise class which
  *         represents various types and names of exercises, including Cardio,
  *         Strength, and Stretching. The class provides methods to convert
  *         between enum values and strings for these exercise types and names.
  *
  ******************************************************************************
  */

#ifndef EXERCISE_H
#define EXERCISE_H

#include <QJsonObject>

enum ExerciseType{
    Cardio,
    Shoulder,
    Chest,
    Back,
    Arm,
    Belly,
    Hip,
    Leg
};

enum ExerciseName{
    TreadmillRunning,
    TreadmillWalking,
    StationaryBike,
    StairClimber,
    BenchPress,
    DumbbellInclinePress,
    LatPulldown,
    BarbellRow,
    OverheadPress,
    DumbbellLateralRaise
};

class Exercise{
public:
    Exercise() = delete;
    Exercise(ExerciseType type, ExerciseName name);
    virtual QJsonObject toJson() const = 0;

    static QString toString(ExerciseType type);
    static QString toString(ExerciseName name);
    static ExerciseType fromStringToExerciseType(const QString& str);
    static ExerciseName fromStringToExerciseName(const QString& str);

    ExerciseType GetType() const;
    ExerciseName GetName() const;

private:
    ExerciseType type_;
    ExerciseName name_;
};

#endif // EXERCISE_H
