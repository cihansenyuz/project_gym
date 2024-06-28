/**
  ******************************************************************************
  * @file    membermanager.hpp
  * @author  Cihan Senyuz
  * @date    20.06.2024
  * @brief   Header for membermanager.cpp file.
  *                 Manages members within a fitness club, including their personal
  *          details, subscription status, measurements, exercise plans, and
  *          archived data. Provides methods for adding new members, updating
  *          member information, handling subscriptions, managing exercise plans,
  *          and accessing archived data.
  *
  *          Reads from a json file, and keeps all members in a QJsonArray. The
  *          member to be edited is chosen by SetCurrentMemberByName(), then using
  *          methods of the object, member is manupilated. Finally, all changes
  *          saved to the QJsonArray upon SaveChangesOnCurrentMember() method.
  *
  ******************************************************************************
  */

#ifndef MEMBERMANAGER_H
#define MEMBERMANAGER_H

#include "member.h"
#include "cardioworkout.h"
#include "strengthworkout.h"

#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QDebug>

class MemberManager
{
public:
    MemberManager();
    Member* GetCurrentMember() const;
    bool SetCurrentMemberByName(const QString &name);
    void RegisterNewMember(const Member &member);
    void SaveChangesOnCurrentMember();
    void DeleteCurrentMember();

private:
    Member* fromJsonObject(QJsonObject &member_json);
    void ParseMeasurements(Member *member, const QJsonArray &measurements_array);
    void ParseSubscriptions(Member *member, const QJsonArray &subscriptions_array);
    void ParseWeeklyExercisePlan(Member *member, const QJsonArray &weekly_exercise_plan_array);
    void ParseArchivedWeeklyExercisePlans(Member *member, const QJsonArray &archived_weekly_exercise_plans_array);
    Exercise* ParseExercise(const QJsonObject &exercise_json);
    bool SaveToFile();

    QJsonArray members_json;
    QString file_path{"../../members.json"};
    Member *current_member; /** points to the member ready to be manipulated */
};

#endif // MEMBERMANAGER_H
