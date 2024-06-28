#include "../inc/cardioworkout.h"

CardioWorkout::CardioWorkout(ExerciseType type, ExerciseName name, short durition)
    : durition_(durition), Exercise(type, name) {}

QJsonObject CardioWorkout::toJson() const {
    QJsonObject json;
    json["type"] = toString(GetType());
    json["name"] = toString(GetName());
    json["durition"] = durition_;
    return json;
}

short CardioWorkout::GetDurition() const{ return durition_; }
