/**
  ******************************************************************************
  * @file    membermanager.h
  * @author  Cihan Senyuz
  * @date    20.06.2024
  * @brief   Header for membermanager.cpp file.
  *                 Implements member management functionalities including
  *          retrieving, registering, updating, and deleting members. Inherits
  *          from JsonContainer to manage JSON-based member data.
  *
  ******************************************************************************
  */

#ifndef MEMBERMANAGER_H
#define MEMBERMANAGER_H

#include "member.h"
#include "jsoncontainer.h"

#include <QJsonObject>
#include <QJsonValue>
#include <QDebug>

class MemberManager : public JsonContainer
{
public:
    MemberManager() = default;
    Member* GetMember(const QString &name) override;
    void RegisterNewMember(const Member &member) override;
    void SaveChangesOnMember(const Member &member) override;
    void DeleteMember(const QString &name) override;
};

#endif // MEMBERMANAGER_H
