/**
  ******************************************************************************
  * @file    exercise.hpp
  * @author  Cihan Senyuz
  * @date    24.06.2024
  * @brief   Header for Exercise namespace
  *                 This file contains struct Exercise, and releated enums.
  *
  ******************************************************************************
  */

#ifndef EXERCISE_H
#define EXERCISE_H

#include <QJsonObject>

namespace Exercise
{

enum ExerciseName{
    unknownName,
    benchPress,
    dumbbellInclinePress,
    latPulldown,
    barbellRow,
    overheadPress,
    dumbbellLateralRaise
};

enum ExerciseType{
    unknownType,
    cardio,
    shoulder,
    chest,
    back,
    arm,
    leg
};

inline QString ToString(const ExerciseType &type){
    switch(type) {
    case cardio: return "cardio";
    case shoulder: return "shoulder";
    case chest: return "chest";
    case back: return "back";
    case arm: return "arm";
    case leg: return "leg";
    default: return "unknownType";
    }
}

inline ExerciseType fromStringExerciseType(const QString &str) {
    if (str == "cardio") return cardio;
    else if (str == "shoulder") return shoulder;
    else if (str == "chest") return chest;
    else if (str == "back") return back;
    else if (str == "arm") return arm;
    else if (str == "leg") return leg;
    else return unknownType;
}


inline QString ToString(const ExerciseName &name){
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
}


struct Exercise_t{
    ExerciseType type;
    ExerciseName name;
    short set;
    short repeat;

    QJsonObject toJson() const {
        QJsonObject json;
        json["type"] = ToString(type);
        json["name"] = ToString(name);
        json["set"] = set;
        json["repeat"] = repeat;
        return json;
    }
};

}

#endif // EXERCISE_H
