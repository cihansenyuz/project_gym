#include "../../../inc/member/exercise/exercise.h"

Exercise::Exercise(ExerciseType type, ExerciseName name)
    : type_(type), name_(name) {}

QString Exercise::toString(ExerciseType type) {
    switch (type) {
    case Cardio: return "Cardio";
    case Shoulder: return "Shoulder";
    case Chest: return "Chest";
    case Back: return "Back";
    case Arm: return "Arm";
    case Belly: return "Belly";
    case Hip: return "Hip";
    case Leg: return "Leg";
    default: return "Unknown Type";
    }
}

QString Exercise::toString(ExerciseName name) {
    switch (name) {
    case TreadmillRunning: return "Treadmill Running";
    case TreadmillWalking: return "Treadmill Walking";
    case StationaryBike: return "Stationary Bike";
    case StairClimber: return "Stair Climber";
    case BenchPress: return "Bench Press";
    case DumbbellInclinePress: return "Dumbbell Incline Press";
    case LatPulldown: return "Lat Pulldown";
    case BarbellRow: return "Barbell Row";
    case OverheadPress: return "Overhead Press";
    case DumbbellLateralRaise: return "Dumbbell Lateral Raise";
    default: return "Unknown Name";
    }
}

ExerciseType Exercise::fromStringToExerciseType(const QString& str) {
    static const std::unordered_map<QString, ExerciseType> strToExerciseType = {
        {"Cardio", Cardio},
        {"Shoulder", Shoulder},
        {"Chest", Chest},
        {"Back", Back},
        {"Arm", Arm},
        {"Belly", Belly},
        {"Hip", Hip},
        {"Leg", Leg}
    };

    auto it = strToExerciseType.find(str);
    if (it != strToExerciseType.end()) {
        return it->second;
    } else {
        throw std::invalid_argument("Unknown ExerciseType string");
    }
}

ExerciseName Exercise::fromStringToExerciseName(const QString& str) {
    static const std::unordered_map<QString, ExerciseName> strToExerciseName = {
        {"Treadmill Running", TreadmillRunning},
        {"Treadmill Walking", TreadmillWalking},
        {"Stationary Bike", StationaryBike},
        {"Stair Climber", StairClimber},
        {"Bench Press", BenchPress},
        {"Dumbbell Incline Press", DumbbellInclinePress},
        {"Lat Pulldown", LatPulldown},
        {"Barbell Row", BarbellRow},
        {"Overhead Press", OverheadPress},
        {"Dumbbell Lateral Raise", DumbbellLateralRaise}
    };

    auto it = strToExerciseName.find(str);
    if (it != strToExerciseName.end()) {
        return it->second;
    } else {
        throw std::invalid_argument("Unknown ExerciseName string");
    }
}

ExerciseType Exercise::GetType() const { return type_; }
ExerciseName Exercise::GetName() const { return name_; }
