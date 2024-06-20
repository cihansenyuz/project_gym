#include "../inc/member.h"

Member::Member(const QString &name, int age, Measurement &first_measurement)
    : name_(name), age_(age), Measurement(first_measurement) {
    all_measurements_.push_back(first_measurement);
}

void Member::SetSubscriptionStartDate(const QDate &start_date, const QDate &end_date){
    subscription_start_date_ = start_date;
    subscription_end_date_ = end_date;
    subscription_ = true;
}

void Member::SetSubscriptionEndDate(const QDate &end_date){
    subscription_end_date_ = end_date;
}

void Member::AddMeasurement(Measurement &new_measurement){
    all_measurements_.push_back(new_measurement);
}

QJsonObject Member::toJson() const{
    QJsonObject json;
    json["name"] = name_;
    json["age"] = age_;
    json["subscription"] = subscription_;
    if (subscription_) {
        json["subscription_start_date"] = subscription_start_date_.toString(Qt::ISODate);
        json["subscription_end_date"] = subscription_end_date_.toString(Qt::ISODate);
    }

    QJsonArray measurementsArray;
    for (const auto &measurement : all_measurements_) {
        measurementsArray.append(measurement.toJson());
    }
    json["measurements"] = measurementsArray;

    return json;
}
