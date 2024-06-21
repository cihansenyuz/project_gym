/**
  ******************************************************************************
  * @file    membermanager.hpp
  * @author  Cihan Senyuz
  * @date    20.06.2024
  * @brief   Header for membermanager.cpp file.
  *                 This file contains the class to manage members saved in a Json
  *          file. Upon creation of instance, reads saved member datas, then using
  *          behaviours, data is manipulated as desired.
  *
  ******************************************************************************
  */

#ifndef MEMBERMANAGER_H
#define MEMBERMANAGER_H

#include "member.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QDebug>

class MemberManager
{
public:
    MemberManager();
    const Member* GetCurrentMember() const;
    void RegisterNewMember(const Member &new_member);
    bool GetMemberByName(const QString &name);
    // unsubscribe a member
    // start subscription of a member
    // delete a member

private:
    Member* fromJsonObject(QJsonObject &member_json);
    void SaveMemberToJson(const Member &member);

    QJsonArray members_json;
    QString file_path{"../../members.json"};
    Member *current_member;
};

#endif // MEMBERMANAGER_H
