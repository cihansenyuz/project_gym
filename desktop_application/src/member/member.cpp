#include "../../inc/member/member.h"

Member::Member(const QString &name, int age)
    : name_(name), age_(age) {}

void Member::SetId(const QString &id) { id_ = id; }
void Member::SetName(const QString &name){ name_ = name; }
void Member::SetAge(int age){ age_ = age; }

void Member::AddMeasurement(const Measurement &new_measurement){
    all_measurements_.push_back(new_measurement);
}

QJsonObject Member::toJson() const{
    QJsonObject json;
    json["id"] = id_;
    json["name"] = name_;
    json["age"] = age_;

    QJsonArray measurementsArray;
    for (const auto &measurement : all_measurements_) {
        measurementsArray.append(measurement.toJson());
    }
    json["measurements"] = measurementsArray;
    json["latest_subscription"] = Subscription::toJson();  /* for the latest one */

    if(archived_subscriptions_.size()){  /* for archived ones */
        QJsonArray subscriptions_array;
        for (const auto &subscription : archived_subscriptions_) {
            subscriptions_array.append(subscription.toJson(true));
        }
        json["archived_subscriptions"] = subscriptions_array;
    }

    if(HasWeeklyExercisePlan()){
        json["exercise_plan"] = WeeklyExercisePlan::toJson();
    }

    if(archived_exercise_plans_.size()){  /* for archived ones */
        QJsonArray exercise_plans_array;
        for (const auto &exercise_plan : archived_exercise_plans_) {
            QJsonObject exercise_plan_json = exercise_plan.toJson();
            exercise_plans_array.append(exercise_plan_json);
        }
        json["archived_exercise_plans"] = exercise_plans_array;
    }

    return json;
}

float Member::GetWeight() const { return all_measurements_.back().GetWeight(); }
float Member::GetShoulder() const { return all_measurements_.back().GetShoulder(); }
float Member::GetChest() const { return all_measurements_.back().GetChest(); }
float Member::GetArm() const { return all_measurements_.back().GetArm(); }
float Member::GetBelly() const { return all_measurements_.back().GetBelly(); }
float Member::GetHip() const { return all_measurements_.back().GetHip(); }
float Member::GetLeg() const { return all_measurements_.back().GetLeg(); }
QDate Member::GetTakenDate() const{ return all_measurements_.back().GetTakenDate(); }
QString Member::GetId() const { return id_; }
QString Member::GetName() const { return name_; }
int Member::GetAge() const { return age_; }
std::vector<Measurement> Member::GetAllMeasurements() const { return all_measurements_; }
Measurement Member::GetLastMeasurements() const { return all_measurements_.back(); }

void Member::AddSubscriptionToArchive(const Subscription &archived){
    archived_subscriptions_.push_back(archived);
}

void Member::EndSubscription(bool update_end_date){
    Subscription::EndSubscription(update_end_date);
    Subscription last_subscription;
    last_subscription.SetSubscriptionPeriod(GetSubscriptionStartDate(), GetSubscriptionEndDate());
    last_subscription.EndSubscription(update_end_date);
    archived_subscriptions_.push_back(last_subscription);
}

std::vector<Subscription> Member::GetAllArchivedSubscriptions(){
    return archived_subscriptions_;
}

void Member::EndExercisePlan(){
    WeeklyExercisePlan::EndWeeklyExercisePlan();
    WeeklyExercisePlan last_exercise_plan(GetWeeklyExercisePlanPeriod().second,
                                          GetWeeklyExercisePlanPeriod().first);
    last_exercise_plan.SetWeeklyExercisePlan(GetWeeklyExercisePlan());
    AddExercisePlanToArchive(last_exercise_plan);
    ClearWeeklyExercisePlan();
}

void Member::AddExercisePlanToArchive(const WeeklyExercisePlan &archived){
    archived_exercise_plans_.push_back(archived);
}
