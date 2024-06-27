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

#include <QJsonObject>

/*enum ExerciseName{
    unknownName,
    benchPress,
    dumbbellInclinePress,
    latPulldown,
    barbellRow,
    overheadPress,
    dumbbellLateralRaise
};*/


enum ExerciseType{
    unknownType,
    cardio,
    strength,
    strecting
};

/*inline QString ToString(const ExerciseName &name){
    switch(name) {
    case benchPress: return "Bench Press";
    case dumbbellInclinePress: return "Dumbbell Incline Press";
    case latPulldown: return "Lat Pull Down";
    case barbellRow: return "Barbell Row";
    case overheadPress: return "Overhead Press";
    case dumbbellLateralRaise: return "Dumbbell Lateral Raise";
    default: return "unknownName";
    }
}

inline ExerciseName fromStringExerciseName(const QString &str) {
    if (str == "Bench Press") return benchPress;
    else if (str == "Dumbbell Incline Press") return dumbbellInclinePress;
    else if (str == "Lat Pull Down") return latPulldown;
    else if (str == "Barbell Row") return barbellRow;
    else if (str == "Overhead Press") return overheadPress;
    else if (str == "Dumbbell Lateral Raise") return dumbbellLateralRaise;
    else return unknownName;
}*/


class Exercise{
public:
    Exercise() = default;
    ExerciseType GetType() const;
    virtual QJsonObject toJson() const = 0;
    ExerciseType fromStringExerciseType(const QString &str);
    QString ToString(const ExerciseType &type);

private:
    ExerciseType type_;
};




#endif // EXERCISE_H
