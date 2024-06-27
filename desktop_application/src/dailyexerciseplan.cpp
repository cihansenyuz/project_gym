#include "../inc/dailyexerciseplan.h"

void DailyExercisePlan::AddNewExercise(const Exercise &new_exercise){
    daily_plan_.push_back(new_exercise);
}

QJsonObject DailyExercisePlan::toJson() const{
    QJsonObject json;
    QJsonArray daily_plan_json;

    for(const auto &exercise : daily_plan_){
        QJsonObject exercise_json = exercise.toJson();
        daily_plan_json.append(exercise_json);
    }

    json["daily_exercise"] = daily_plan_json.toObject();
    json["cooldown_period"] = cooldown_period_;
    return json;
}

void DailyExercisePlan::GetCooldownPeriod() const{
    return cooldown_period_;
}
