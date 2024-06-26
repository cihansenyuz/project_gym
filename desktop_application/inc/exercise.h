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

class Exercise{
public:
    Exercise() = default;
    Exercise(ExerciseType type, ExerciseName name, short set,
             short repeat, short cooldown_period,
             const QDate &last_done_date = QDate::currentDate());
    void MarkExerciseDone();
    bool IsReady();

    ExerciseType GetType() const;
    ExerciseName GetName() const;
    short GetSet() const;
    short GetRepeat() const;
    short GetCoolDownPeriod() const;
    QDate GetLastDoneDate() const;

    QJsonObject toJson() const;

private:
    ExerciseType type_;
    ExerciseName name_;
    short set_;
    short repeat_;
    short cooldown_period_;
    QDate last_done_date_;
};

}



#endif // EXERCISE_H
