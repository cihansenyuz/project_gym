#ifndef MEMBER_H
#define MEMBER_H

#include <QString>
#include "measurement.h"

class Member : public Measurement
{
public:
    Member(const QString &name, int age, Measurement &first_measurement);
    void SetSubscriptionStartDate(const QDate &start_date, const QDate &end_date);
    void SetSubscriptionEndDate(const QDate &end_date);
    void AddMeasurement(Measurement &new_measurement);

private:
    QString name_;
    int age_;
    bool subscription_{false};
    QDate subscription_start_date_;
    QDate subscription_end_date_;
    std::vector<Measurement> all_measurements_;
};

#endif // MEMBER_H
