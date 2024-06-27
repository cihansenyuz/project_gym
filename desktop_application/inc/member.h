/**
  ******************************************************************************
  * @file    member.hpp
  * @author  Cihan Senyuz
  * @date    16.06.2024
  * @brief   Header for member.cpp file.
  *                 Represents a member with age, measurements, exercise plans,
  *          and subscription details. Provides methods for managing member data
  *          and subscriptions.
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
#include "weeklyexerciseplan.h"

/**
 *  NOTE: In case any property changes done to the class,
 *  toJson behaviour must be revised. Also, fromJsonObject
 *  behaviour of MemberManager class must be revised!
 *
 */
class Member : public Measurement, public Subscription, public WeeklyExercisePlan
{
public:
    Member() = default;
    Member(const QString &name, int age, Measurement &first_measurement);
    QJsonObject toJson() const;

    void SetName(const QString &name);
    void SetAge(int age);
    void AddMeasurement(Measurement &new_measurement);
    void AddSubscriptionToArchive(const Subscription &archived);
    void EndSubscription();
    void AddExercisePlanToArchive(const WeeklyExercisePlan &archived);
    void ArchiveCurrentExercisePlan();

    float GetWeight() const;
    float GetShoulder() const;
    float GetChest() const;
    float GetArm() const;
    float GetBelly() const;
    float GetHip() const;
    float GetLeg() const;
    QDate GetTakenDate() const;
    QString GetName() const;
    int GetAge() const;
    Measurement GetLastMeasurements() const;
    std::vector<Measurement> GetAllMeasurements() const;
    std::vector<Subscription> GetAllArchivedSubscriptions();

private:
    QString name_;
    int age_;
    std::vector<Measurement> all_measurements_;
    std::vector<Subscription> archived_subscriptions_;
    std::vector<WeeklyExercisePlan> archived_exercise_plans_;
};

#endif // MEMBER_H
