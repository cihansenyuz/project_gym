#include "../inc/strengthworkout.h"

StrengthWorkout::StrengthWorkout(ExerciseType type, ExerciseName name, short set, short repeat)
    : set_(set), repeat_(repeat), Exercise(type, name) {}

QJsonObject StrengthWorkout::toJson() const override{
    QJsonObject json;
    json["type"] = toString(GetType());
    json["name"] = toString(GetName());
    json["set"] = set_;
    json["repeat"] = repeat_;
    return json;
}

short StrengthWorkout::GetSet() const{ return set_; }
short StrengthWorkout::GetRepeat() const{ return repeat_; }
