#include "../inc/exercise.h"

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
    case TreadmillRunning: return "TreadmillRunning";
    case TreadmillWalking: return "TreadmillWalking";
    case StationaryBike: return "StationaryBike";
    case StairClimber: return "StairClimber";
    case BenchPress: return "BenchPress";
    case DumbbellInclinePress: return "DumbbellInclinePress";
    case LatPulldown: return "LatPulldown";
    case BarbellRow: return "BarbellRow";
    case OverheadPress: return "OverheadPress";
    case DumbbellLateralRaise: return "DumbbellLateralRaise";
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
        {"TreadmillRunning", TreadmillRunning},
        {"TreadmillWalking", TreadmillWalking},
        {"StationaryBike", StationaryBike},
        {"StairClimber", StairClimber},
        {"BenchPress", BenchPress},
        {"DumbbellInclinePress", DumbbellInclinePress},
        {"LatPulldown", LatPulldown},
        {"BarbellRow", BarbellRow},
        {"OverheadPress", OverheadPress},
        {"DumbbellLateralRaise", DumbbellLateralRaise}
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
