/**
  ******************************************************************************
  * @file    jsoncontainer.h
  * @author  Cihan Senyuz
  * @date    30.06.2024
  * @brief   Header for jsoncontainer.cpp file.
  *                 Manages a collection of Member objects, providing methods
  *          for registering new members, saving changes, and deleting members.
  *          Inherits from JsonParser to utilize JSON parsing functionality.
  *
  ******************************************************************************
  */

#ifndef JSONCONTAINER_H
#define JSONCONTAINER_H

#include "member.h"
#include "jsonparser.h"

#include <QJsonArray>
#include <QJsonDocument>
#include <QFile>

class JsonContainer : public JsonParser
{
public:
    JsonContainer();
    virtual void RegisterNewMember(const Member &member) = 0;
    virtual void SaveChangesOnMember(const Member &member) = 0;
    virtual void DeleteMember(const QString &name) = 0;
    friend class MemberManager;

private:
    bool SaveToFile();

    QString file_path{"../../members.json"};
    QJsonArray members_array;
};

#endif // JSONCONTAINER_H
