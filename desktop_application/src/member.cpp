#include "../inc/member.h"

Member::Member(const QString &name, int age, Measurement &first_measurement)
    : name_(name), age_(age), Measurement(first_measurement) {}

void Member::SetSubscriptionStartDate(const QDate &start_date, const QDate &end_date){
    subscription_start_date_ = start_date;
    subscription_end_date_ = end_date;
}

void Member::SetSubscriptionEndDate(const QDate &end_date){
    subscription_end_date_ = end_date;
}

void Member::AddMeasurement(Measurement &new_measurement){
    all_measurements_.push_back(new_measurement);
}
