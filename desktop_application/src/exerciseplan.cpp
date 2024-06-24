#include "../inc/exerciseplan.h"

void ExercisePlan::AddNewExercise(const Exercise::Exercise_t &new_exercise,  short cooldown_days){
    weekly_plan_["T+"+QString::number(cooldown_days)] = new_exercise;
}

void ExercisePlan::SetTargetDate(const QDate &end_day){
    start_day_ = QDate::currentDate();
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
