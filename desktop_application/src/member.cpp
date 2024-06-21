#include "../inc/member.h"

Member::Member(const QString &name, int age, Measurement &first_measurement)
    : name_(name), age_(age), Measurement(first_measurement) {

    all_measurements_.push_back(first_measurement);
    if(subscription_end_date_ < QDate::currentDate())
        EndSubscription();
}

void Member::SetName(const QString &name){ name_ = name; }

void Member::SetAge(int age){ age_ = age; }

void Member::SetSubscriptionPeriod(const QDate &start_date, const QDate &end_date){
    subscription_start_date_ = start_date;
    subscription_end_date_ = end_date;
    if(end_date > QDate::currentDate())
        subscription_ = true;
}

void Member::ExtendSubscriptionEndDate(const QDate &end_date){
    subscription_end_date_ = end_date;
}

void Member::EndSubscription(){
    subscription_ = false;
    subscription_end_date_ = QDate::currentDate();
}

void Member::AddMeasurement(Measurement &new_measurement){
    all_measurements_.push_back(new_measurement);
}

QJsonObject Member::toJson() const{
    QJsonObject json;
    json["name"] = name_;
    json["age"] = age_;
    json["subscription"] = subscription_;
    json["subscription_start_date"] = subscription_start_date_.toString(Qt::ISODate);
    json["subscription_end_date"] = subscription_end_date_.toString(Qt::ISODate);

    QJsonArray measurementsArray;
    for (const auto &measurement : all_measurements_) {
        measurementsArray.append(measurement.toJson());
    }
    json["measurements"] = measurementsArray;

    return json;
}

float Member::GetWeight(int measurement_no) const {
    return all_measurements_.at(--measurement_no).GetWeight();
}

float Member::GetShoulder(int measurement_no) const {
    return all_measurements_.at(--measurement_no).GetShoulder();
}

float Member::GetChest(int measurement_no) const {
    return all_measurements_.at(--measurement_no).GetChest();
}

float Member::GetArm(int measurement_no) const {
    return all_measurements_.at(--measurement_no).GetArm();
}

float Member::GetBelly(int measurement_no) const {
    return all_measurements_.at(--measurement_no).GetBelly();
}

float Member::GetHip(int measurement_no) const {
    return all_measurements_.at(--measurement_no).GetHip();
}

float Member::GetLeg(int measurement_no) const {
    return all_measurements_.at(--measurement_no).GetLeg();
}

QDate Member::GetTakenDate(int measurement_no) const{
    return all_measurements_.at(--measurement_no).GetTakenDate();
}

QString Member::GetName() const { return name_; }
int Member::GetAge() const { return age_; }
bool Member::HasSubscription() const { return subscription_; }
QDate Member::GetSubscriptionStartDate() const { return subscription_start_date_; }
QDate Member::GetSubscriptionEndDate() const { return subscription_end_date_; }

std::vector<Measurement> Member::GetAllMeasurements() const {
    return all_measurements_;
}

Measurement Member::GetLastMeasurements() const {
    return all_measurements_.back();
}
