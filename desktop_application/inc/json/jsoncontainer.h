/**
  ******************************************************************************
  * @file    jsoncontainer.h
  * @author  Cihan Senyuz
  * @date    30.06.2024
  * @brief   Header for jsoncontainer.cpp file.
  *                 Provides an interface to manage a collection of Member objects,
  *          providing methods for registering new members, saving changes, and
  *          deleting members.
  *
  ******************************************************************************
  */

#ifndef JSONCONTAINER_H
#define JSONCONTAINER_H

#include "../member/member.h"
#include "../json/jsonparser.h"

#include <QJsonArray>
#include <QJsonDocument>
#include <QFile>

class JsonContainer
{
public:
    JsonContainer() = default;
    virtual void RegisterNewMember(const Member &member) = 0;
    virtual void SaveChangesOnMember(const Member &member) = 0;
    virtual void DeleteMember(const QString &name) = 0;
    friend class MemberManager;
    void LoadFromFile();
    QJsonArray* GetMemberArrayData();

private:
    bool SaveToFile();

    QString file_path{"../../members.json"};
    QJsonArray members_array;
};

#endif // JSONCONTAINER_H
