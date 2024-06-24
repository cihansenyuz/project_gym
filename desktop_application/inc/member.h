/**
  ******************************************************************************
  * @file    member.hpp
  * @author  Cihan Senyuz
  * @date    16.06.2024
  * @brief   Header for member.cpp file.
  *                 This file contains the class for each membe. The class inherets
  *          Measurement class, so that the class encapsulates all measurements of
  *          a member, personal information and subscription information. Also,
  *          provides a method to convert all data to JSON format using QJsonObject
  *
  ******************************************************************************
  */

#ifndef MEMBER_H
#define MEMBER_H

#include <QString>
#include <QJsonObject>
#include <QJsonArray>
#include "measurement.h"
#include "subscription.h"

/**
 *  NOTE: In case any property changes done to the class,
 *  toJson behaviour must be revised. Also,
 *  fromJsonObject, SaveUpdatedCurrentMember behaviours of
 *  MemberManager class must be revised!
 */
class Member : public Measurement, public Subscription
{
public:
    Member() = default;
    Member(const QString &name, int age, Measurement &first_measurement);
    void SetName(const QString &name);
    void SetAge(int age);
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
    std::vector<Measurement> GetAllMeasurements() const;
    Measurement GetLastMeasurements() const;
    void AddArchivedSubscription(const Subscription &archived);
    void EndSubscription();

private:
    QString name_;
    int age_;
    std::vector<Measurement> all_measurements_;
    std::vector<Subscription> archived_subscriptions_;
};

#endif // MEMBER_H
