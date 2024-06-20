#include "../inc/member.h"

Member::Member(const QString &name, int age)
    : name_(name), age_(age) {

}

void Member::SetSubscriptionStartDate(const QDate &start_date, const QDate &end_date){
    start_date_ = start_date;
    end_date_ = end_date;
}

void Member::SetSubscriptionEndDate(const QDate &end_date){
    end_date_ = end_date;
}

void Member::AddMeasurement(Measurement &new_measurement){
    all_measurements_.push_back(new_measurement);
}
