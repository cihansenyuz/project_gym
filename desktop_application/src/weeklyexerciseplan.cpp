#include "../inc/weeklyexerciseplan.h"

WeeklyExercisePlan::WeeklyExercisePlan(const QDate &end_date, const QDate &start_date)
    : start_date_(start_date), end_date_(end_date) {}

QJsonObject WeeklyExercisePlan::toJson() const{
    QJsonObject json;
    QJsonArray weekly_plan_array;

    for(const auto &daily_plan : weekly_plan_){
        QJsonObject daily_plan_json = daily_plan.toJson();
        weekly_plan_array.append(daily_plan_json);
    }

    json["weekly_exercise_plan"] = weekly_plan_array;
    json["start_date"] = start_date_.toString(Qt::ISODate);
    json["end_date"] = end_date_.toString(Qt::ISODate);
    return json;
}

void WeeklyExercisePlan::AddNewDailyExercisePlan(const DailyExercisePlan &new_daily_plan){
    weekly_plan_.push_back(new_daily_plan);
}

void WeeklyExercisePlan::ClearWeeklyExercisePlan(){
    weekly_plan_.clear();
}

void WeeklyExercisePlan::SetWeeklyExercisePlan(const std::vector<DailyExercisePlan> &new_weekly_plan){
    weekly_plan_ = new_weekly_plan;
}

void WeeklyExercisePlan::SetWeeklyExercisePlanPeriod(QDate start_date, QDate end_date){
    start_date_ = start_date;
    end_date_ = end_date;
}

short WeeklyExercisePlan::GetRemaningDays(){
    return QDate::currentDate().daysTo(end_date_);
}

bool WeeklyExercisePlan::HasWeeklyExercisePlan() const{
    return weekly_plan_.size();
}

std::pair<QDate, QDate> WeeklyExercisePlan::GetWeeklyExercisePlanPeriod(){
    return std::make_pair(start_date_, end_date_);
}

std::vector<DailyExercisePlan> WeeklyExercisePlan::GetWeeklyExercisePlan(){
    return weekly_plan_;
}
