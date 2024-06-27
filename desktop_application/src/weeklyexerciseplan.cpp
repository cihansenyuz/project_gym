#include "../inc/weeklyexerciseplan.h"

WeeklyExercisePlan(const QDate &end_date, const QDate &start_date)
    : start_date_(start_date), end_date_(end_date) {}

QJsonObject WeeklyExercisePlan::toJson() const{
    QJsonObject json;
    QJsonArray weekly_plan_json;

    for(const auto &daily_plan : weekly_plan_){
        QJsonObject daily_plan_json = daily_plan.toJson();
        weekly_plan_json.append(daily_plan_json);
    }

    json["weekly_exercise_plan"] = weekly_plan_json.toObject();
    json["start_date"] = start_date_.toString(Qt::ISODate);
    json["end_date"] = end_date_.toString(Qt::ISODate);
    return json;
}

void WeeklyExercisePlan::AddNewExercise(const DailyExercisePlan &new_daily_plan){
    weekly_plan_.push_back(new_daily_plan);
}

void WeeklyExercisePlan::ClearWeeklyExercisePlan(){
    weekly_plan_.clear();
}

short WeeklyExercisePlan::GetRemaningDays(){
    return QDate::currentDate().daysTo(end_date_);
}

std::pair<QDate, QDate> WeeklyExercisePlan::GetWeeklyExercisePlanPeriod(){
    return std::make_pair(start_date_, end_date_);
}
