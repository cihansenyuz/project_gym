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



private:



    QJsonArray members_json;
    QString file_path{"../../members.json"};
};

#endif // MEMBERMANAGER_H
