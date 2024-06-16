#include "../inc/member.h"

Member::Member(const QString &name, int age, float weight)
    : name_(name), age_(age), weight_(weight) {

}

void Member::SetSubscriptionStartDate(const QDate &start_date, const QDate &end_date){
    start_date_ = start_date;
    end_date_ = end_date;
}

void Member::SetSubscriptionEndDate(const QDate &end_date){
    end_date_ = end_date;
}

void Member::SetWeight(float weight){
    weight_ = weight;
}
