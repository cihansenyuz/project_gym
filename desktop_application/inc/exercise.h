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

namespace Exercise
{

enum ExerciseName{
    benchPress,
    dumbbellInclinePress,
    latPulldown,
    barbellRow,
    overheadPress,
    dumbbellLateralRaise
    // etc.
};

enum ExerciseType{
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
    default: return "unknown";
    }
}

inline QString ToString(const ExerciseName &name){
    switch(name) {
    case benchPress: return "Bench Press";
    case dumbbellInclinePress: return "Dumbbell Incline Press";
    case latPulldown: return "Lat Pull Down";
    case barbellRow: return "Barbell Row";
    case overheadPress: return "Overhead Press";
    case dumbbellLateralRaise: return "Dumbbell Lateral Raise";
    default: return "unknown";
    }
}

struct Exercise_t{
    ExerciseType type;
    ExerciseName name;
    short set;
    short repeat;
};

}

#endif // EXERCISE_H
