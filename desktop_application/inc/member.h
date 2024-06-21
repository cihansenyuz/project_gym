#ifndef MEMBER_H
#define MEMBER_H

#include <QString>
#include <QJsonObject>
#include <QJsonArray>
#include "measurement.h"

class Member : public Measurement
{
public:
    Member() = default;
    Member(const QString &name, int age, Measurement &first_measurement);
    void SetName(const QString &name);
    void SetAge(int age);
    void SetSubscriptionPeriod(const QDate &start_date, const QDate &end_date);
    void ExtendSubscriptionEndDate(const QDate &end_date);
    void EndSubscription();
    void AddMeasurement(Measurement &new_measurement);
    QJsonObject toJson() const;

    float GetWeight(int measurement_no) const;
    float GetShoulder(int measurement_no) const;
    float GetChest(int measurement_no) const;
    float GetArm(int measurement_no) const;
    float GetBelly(int measurement_no) const;
    float GetHip(int measurement_no) const;
    float GetLeg(int measurement_no) const;
    QDate GetTakenDate(int measurement_no) const;
    QString GetName() const;
    int GetAge() const;
    bool HasSubscription() const;
    QDate GetSubscriptionStartDate() const;
    QDate GetSubscriptionEndDate() const;
    std::vector<Measurement> GetAllMeasurements() const;
    Measurement GetLastMeasurements() const;

private:
    QString name_;
    int age_;
    bool subscription_{false};
    QDate subscription_start_date_;
    QDate subscription_end_date_;
    std::vector<Measurement> all_measurements_;
};

#endif // MEMBER_H
