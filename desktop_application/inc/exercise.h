/**
  ******************************************************************************
  * @file    exercise.hpp
  * @author  Cihan Senyuz
  * @date    24.06.2024
  * @brief   Header for exercise.cpp file.
  *                 Represents a specific exercise within an exercise plan,
  *          detailing its name, cooldown period, repetitions, sets, and type
  *          (e.g., chest, back, leg). Provides methods for managing exercise
  *          details and tracking completion.
  *
  ******************************************************************************
  */

#ifndef EXERCISE_H
#define EXERCISE_H

#include <map>
#include <QString>

class Exercise{
public:
    Exercise() = delete;
    Exercise(ExerciseType type, ExerciseName name);
    virtual QJsonObject toJson() const = 0;
    ExerciseType GetType() const;

    ExerciseType::Cardio fromStringCardio(const QString &str);
    ExerciseType::Strength fromStringStrength(const QString &str);
    ExerciseType::Stretching fromStringStretching(const QString &str);
    QString toString(const ExerciseType::Cardio &type);
    QString toString(const ExerciseType::Strength &type);
    QString toString(const ExerciseType::Stretching &type);

    ExerciseName::Cardio fromStringExerciseNameCardio(const QString &str);
    ExerciseName::Strength fromStringExerciseNameStrength(const QString &str);
    ExerciseName::Stretching fromStringExerciseNameStretching(const QString &str);
    QString toString(const ExerciseName::Cardio &type);
    QString toString(const ExerciseName::Strength &type);
    QString toString(const ExerciseName::Stretching &type);

    struct ExerciseType{
        enum class Cardio{
            Cardio
        };

        enum class Strength{
            Shoulder,
            Chest,
            Back,
            Arm,
            Belly,
            Hip,
            Leg
        };

        enum class Stretching{
            Stretching
        };
    };

    struct ExerciseName{
        enum class Cardio{
            TreadmillRunning,
            TreadmillWalking,
            StationaryBike,
            StairClimber
        };

        enum class Strength{
            BenchPress,
            DumbbellInclinePress,
            LatPulldown,
            BarbellRow,
            OverheadPress,
            DumbbellLateralRaise
        };

        enum class Stretching{
            Hamstring,
            Quadriceps,
            HipFlexor
        };
    };

private:
    ExerciseType type_;
    ExerciseName name_;
};

#endif // EXERCISE_H
