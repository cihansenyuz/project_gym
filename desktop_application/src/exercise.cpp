#include "../inc/exercise.h"

Exercise::Exercise(ExerciseType type, ExerciseName name)
    : type_(type), name_(name) {}

Exercise::ExerciseType::Cardio Exercise::fromStringCardio(const QString &str) {
    static std::map<QString, ExerciseType::Cardio> cardio_map = {
        {"Cardio", ExerciseType::Cardio::Cardio}
    };

    return cardio_map[str];
}

Exercise::ExerciseType::Strength Exercise::fromStringStrength(const QString &str) {
    static std::map<QString, ExerciseType::Strength> strength_map = {
        {"Shoulder", ExerciseType::Strength::Shoulder},
        {"Chest", ExerciseType::Strength::Chest},
        {"Back", ExerciseType::Strength::Back},
        {"Arm", ExerciseType::Strength::Arm},
        {"Belly", ExerciseType::Strength::Belly},
        {"Hip", ExerciseType::Strength::Hip},
        {"Leg", ExerciseType::Strength::Leg}
    };

    return strength_map[str];
}

Exercise::ExerciseType::Stretching Exercise::fromStringStretching(const QString &str) {
    static std::map<QString, ExerciseType::Stretching> stretching_map = {
        {"Stretching", ExerciseType::Stretching::Stretching}
    };

    return stretching_map[str];
}

QString Exercise::toString(const ExerciseType::Cardio &type) {
    static std::map<ExerciseType::Cardio, QString> cardio_map = {
        {ExerciseType::Cardio::Cardio, "Cardio"}
    };

    return cardio_map[type];
}

QString Exercise::toString(const ExerciseType::Strength &type) {
    static std::map<ExerciseType::Strength, QString> strength_map = {
        {ExerciseType::Strength::Shoulder, "Shoulder"},
        {ExerciseType::Strength::Chest, "Chest"},
        {ExerciseType::Strength::Back, "Back"},
        {ExerciseType::Strength::Arm, "Arm"},
        {ExerciseType::Strength::Belly, "Belly"},
        {ExerciseType::Strength::Hip, "Hip"},
        {ExerciseType::Strength::Leg, "Leg"}
    };

    return strength_map[type];
}

QString Exercise::toString(const ExerciseType::Stretching &type) {
    static std::map<ExerciseType::Stretching, QString> stretching_map = {
        {ExerciseType::Stretching::Stretching, "Stretching"}
    };

    return stretching_map[type];
}

Exercise::ExerciseType::Cardio Exercise::fromStringCardio(const QString &str) {
    static std::map<QString, ExerciseType::Cardio> cardio_map = {
        {"cardio", ExerciseType::Cardio::cardio}
    };

    return cardio_map[str];
}

Exercise::ExerciseType::Strength Exercise::fromStringStrength(const QString &str) {
    static std::map<QString, ExerciseType::Strength> strengthMap = {
        {"shoulder", ExerciseType::Strength::shoulder},
        {"chest", ExerciseType::Strength::chest},
        {"back", ExerciseType::Strength::back},
        {"arm", ExerciseType::Strength::arm},
        {"belly", ExerciseType::Strength::belly},
        {"hip", ExerciseType::Strength::hip},
        {"leg", ExerciseType::Strength::leg}
    };

    return strength_map[str];
}

Exercise::ExerciseType::Stretching Exercise::fromStringStretching(const QString &str) {
    static std::map<QString, ExerciseType::Stretching> stretchingMap = {
        {"stretching", ExerciseType::Stretching::stretching}
    };

    return stretching_map[str];
}

QString Exercise::toString(const ExerciseType::Cardio &type) {
    static std::map<ExerciseType::Cardio, QString> cardio_map = {
        {ExerciseType::Cardio::cardio, "cardio"}
    };

    return cardio_map[type];
}

QString Exercise::toString(const ExerciseType::Strength &type) {
    static std::map<ExerciseType::Strength, QString> strength_map = {
        {ExerciseType::Strength::shoulder, "shoulder"},
        {ExerciseType::Strength::chest, "chest"},
        {ExerciseType::Strength::back, "back"},
        {ExerciseType::Strength::arm, "arm"},
        {ExerciseType::Strength::belly, "belly"},
        {ExerciseType::Strength::hip, "hip"},
        {ExerciseType::Strength::leg, "leg"}
    };

    return strength_map[type];
}

QString Exercise::toString(const ExerciseType::Stretching &type) {
    static std::map<ExerciseType::Stretching, QString> stretching_map = {
        {ExerciseType::Stretching::stretching, "stretching"}
    };

    return stretching_map[type];
}

// Definitions for ExerciseName to/from string functions
Exercise::ExerciseName::Cardio Exercise::fromStringExerciseNameCardio(const QString &str) {
    static std::map<QString, ExerciseName::Cardio> cardio_map = {
        {"TreadmillRunning", ExerciseName::Cardio::TreadmillRunning},
        {"TreadmillWalking", ExerciseName::Cardio::TreadmillWalking},
        {"StationaryBike", ExerciseName::Cardio::StationaryBike},
        {"StairClimber", ExerciseName::Cardio::StairClimber}
    };

    return cardio_map[str];
}

Exercise::ExerciseName::Strength Exercise::fromStringExerciseNameStrength(const QString &str) {
    static std::map<QString, ExerciseName::Strength> strength_map = {
        {"BenchPress", ExerciseName::Strength::BenchPress},
        {"DumbbellInclinePress", ExerciseName::Strength::DumbbellInclinePress},
        {"LatPulldown", ExerciseName::Strength::LatPulldown},
        {"BarbellRow", ExerciseName::Strength::BarbellRow},
        {"OverheadPress", ExerciseName::Strength::OverheadPress},
        {"DumbbellLateralRaise", ExerciseName::Strength::DumbbellLateralRaise}
    };

    return strength_map[str];
}

Exercise::ExerciseName::Stretching Exercise::fromStringExerciseNameStretching(const QString &str) {
    static std::map<QString, ExerciseName::Stretching> stretching_map = {
        {"Hamstring", ExerciseName::Stretching::Hamstring},
        {"Quadriceps", ExerciseName::Stretching::Quadriceps},
        {"HipFlexor", ExerciseName::Stretching::HipFlexor}
    };

    return stretching_map[str];
}

QString Exercise::toString(const ExerciseName::Cardio &type) {
    static std::map<ExerciseName::Cardio, QString> cardio_map = {
        {ExerciseName::Cardio::TreadmillRunning, "TreadmillRunning"},
        {ExerciseName::Cardio::TreadmillWalking, "TreadmillWalking"},
        {ExerciseName::Cardio::StationaryBike, "StationaryBike"},
        {ExerciseName::Cardio::StairClimber, "StairClimber"}
    };

    return cardio_map[type];
}

QString Exercise::toString(const ExerciseName::Strength &type) {
    static std::map<ExerciseName::Strength, QString> strength_map = {
        {ExerciseName::Strength::BenchPress, "BenchPress"},
        {ExerciseName::Strength::DumbbellInclinePress, "DumbbellInclinePress"},
        {ExerciseName::Strength::LatPulldown, "LatPulldown"},
        {ExerciseName::Strength::BarbellRow, "BarbellRow"},
        {ExerciseName::Strength::OverheadPress, "OverheadPress"},
        {ExerciseName::Strength::DumbbellLateralRaise, "DumbbellLateralRaise"}
    };

    return strength_map[type];
}

QString Exercise::toString(const ExerciseName::Stretching &type) {
    static std::map<ExerciseName::Stretching, QString> stretching_map = {
        {ExerciseName::Stretching::Hamstring, "Hamstring"},
        {ExerciseName::Stretching::Quadriceps, "Quadriceps"},
        {ExerciseName::Stretching::HipFlexor, "HipFlexor"}
    };

    return stretching_map[type];
}

Exercise::ExerciseType Exercise::GetType() const{ return type_; }
Exercise::ExerciseName Exercise::GetType() const{ return name_; }
