#include "../../../inc/member/exercise/dailyexerciseplan.h"

void DailyExercisePlan::AddNewExercise(Exercise *new_exercise){
    daily_plan_.push_back(new_exercise);
}

QJsonObject DailyExercisePlan::toJson() const{
    QJsonObject json;
    QJsonArray daily_plan_json;

    for(const auto &exercise : daily_plan_){
        QJsonObject exercise_json = exercise->toJson();
        daily_plan_json.append(exercise_json);
    }

    json["daily_exercise"] = daily_plan_json;
    json["cooldown_period"] = cooldown_period_;
    return json;
}

void DailyExercisePlan::SetCooldownPeriod(short days){
    cooldown_period_ = days;
}

void DailyExercisePlan::SetDailyExecisePlan(const std::vector<Exercise*> &new_plan){
    daily_plan_ = new_plan;
}

short DailyExercisePlan::GetCooldownPeriod() const{
    return cooldown_period_;
}

std::vector<Exercise*> DailyExercisePlan::GetDailyExercisePlan() const{
    return daily_plan_;
}
