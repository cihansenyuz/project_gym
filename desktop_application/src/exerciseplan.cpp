#include "../inc/exerciseplan.h"

void ExercisePlan::AddNewExercise(const Exercise::Exercise_t &new_exercise,  short cooldown_days){
    weekly_plan_["T+"+QString::number(cooldown_days)] = new_exercise;
}

std::map<QString, Exercise::Exercise_t> ExercisePlan::GetWeeklyPlan() const{
    return weekly_plan_;
}

void ExercisePlan::SetTargetDate(const QDate &end_day, const QDate &start_day){
    start_day_ = start_day;
    end_day_ = end_day;
}

short ExercisePlan::RemaningDays(){
    return QDate::currentDate().daysTo(end_day_);
}

void ExercisePlan::PrintPlan(){
    qDebug() << "Remaining: " << RemaningDays() << " days";
    for(auto &[key, value] : weekly_plan_){
        qDebug() << "## Exercise details ##";
        qDebug() << "valor:" << key << "type: " << Exercise::ToString(value.type);
        qDebug() << Exercise::ToString(value.name) << ": " << value.set << "sets, " << value.repeat << "repeats.";
    }
}

std::pair<QDate, QDate> ExercisePlan::GetExercisePeriod(){
    return std::make_pair(start_day_, end_day_);
}

void ExercisePlan::ClearExercisePlan(){
    weekly_plan_.clear();
    start_day_ = QDate::currentDate();
    end_day_ = QDate::currentDate();
}

void ExercisePlan::SetWeeklyPlan(const std::map<QString, Exercise::Exercise_t> &weekly_plan){
    weekly_plan_ = weekly_plan;
}

QJsonObject ExercisePlan::toJson() const{
    QJsonObject json;
    json["start_day"] = start_day_.toString(Qt::ISODate);
    json["end_day"] = end_day_.toString(Qt::ISODate);

    QJsonArray weekly_plan_array;
    for(auto &plan : weekly_plan_){
        QJsonObject exercise_json;
        exercise_json["valor"] = plan.first;
        exercise_json["exercise"] = plan.second.toJson();
        weekly_plan_array.append(exercise_json);
    }

    json["weekly_plan"] = weekly_plan_array;
    return json;
}
