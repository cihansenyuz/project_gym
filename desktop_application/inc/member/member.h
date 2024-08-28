/**
  ******************************************************************************
  * @file    member.hpp
  * @author  Cihan Senyuz
  * @date    16.06.2024
  * @brief   Header for member.cpp file.
  *             This file contains the definition of the Member class, which
  *         represents a member of a fitness program. The class includes properties
  *         and methods for managing the member's personal information, measurements,
  *         subscriptions, and exercise plans.
  *
  * @note   In case any property changes are made to the class, the toJson behavior
  *         must be revised. Also, the fromJsonObject behavior of the MemberManager
  *         class must be revised!
  *
  ******************************************************************************
  */

#ifndef MEMBER_H
#define MEMBER_H

#include "measurement.h"
#include "subscription/subscription.h"
#include "exercise/weeklyexerciseplan.h"

/**
 *  @note In case any property changes done to the class,
 *  toJson behaviour must be revised. Also, fromJsonObject
 *  behaviour of MemberManager class must be revised!
 *
 */
class Member : public Subscription, public WeeklyExercisePlan
{
public:
    Member() = default;
    Member(const QString &name, int age);
    QJsonObject toJson() const;

    void SetId(const QString &id);
    void SetName(const QString &name);
    void SetAge(int age);
    void AddMeasurement(const Measurement &new_measurement);
    void AddSubscriptionToArchive(const Subscription &archived);
    void EndSubscription(bool update_end_date = true);
    void AddExercisePlanToArchive(const WeeklyExercisePlan &archived);
    void EndExercisePlan();

    float GetWeight() const;
    float GetShoulder() const;
    float GetChest() const;
    float GetArm() const;
    float GetBelly() const;
    float GetHip() const;
    float GetLeg() const;
    QDate GetTakenDate() const;
    QString GetId() const;
    QString GetName() const;
    int GetAge() const;
    Measurement GetLastMeasurements() const;
    std::vector<Measurement> GetAllMeasurements() const;
    std::vector<Subscription> GetAllArchivedSubscriptions();

private:
    QString id_;
    QString name_;
    int age_;
    std::vector<Measurement> all_measurements_;
    std::vector<Subscription> archived_subscriptions_;
    std::vector<WeeklyExercisePlan> archived_exercise_plans_;
};

#endif // MEMBER_H
