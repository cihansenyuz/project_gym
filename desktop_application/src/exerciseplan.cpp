#include "../inc/exerciseplan.h"

void ExercisePlan::AddNewExercise(const Exercise::Exercise &new_exercise){
    weekly_plan_.push_back(new_exercise);
}

std::vector<Exercise::Exercise> ExercisePlan::GetWeeklyPlan() const{
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
    for(auto &exercise : weekly_plan_){
        qDebug() << "## Exercise details ##";
        qDebug() << "cooldown:" << exercise.GetCoolDownPeriod() << "type: " << Exercise::ToString(exercise.GetType());
        qDebug() << Exercise::ToString(exercise.GetName()) << ": " << exercise.GetSet() << "sets, " << exercise.GetRepeat() << "repeats.";
        qDebug() << "Last exercise date: " << exercise.GetLastDoneDate().toString();
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

void ExercisePlan::SetWeeklyPlan(const std::vector<Exercise::Exercise> &weekly_plan){
    weekly_plan_ = weekly_plan;
}

QJsonObject ExercisePlan::toJson() const{
    QJsonObject json;
    json["start_day"] = start_day_.toString(Qt::ISODate);
    json["end_day"] = end_day_.toString(Qt::ISODate);

    QJsonArray weekly_plan_array;
    for(auto &plan : weekly_plan_){
        QJsonObject exercise_json = plan.toJson();
        weekly_plan_array.append(exercise_json);
    }

    json["weekly_plan"] = weekly_plan_array;
    return json;
}
