/**
  ******************************************************************************
  * @file    membermanager.h
  * @author  Cihan Senyuz
  * @date    20.06.2024
  * @brief   Header for membermanager.cpp file.
  *                 Implements member management functionalities including
  *          retrieving, registering, updating, and deleting members. Inherits
  *          from JsonContainer to read/write data to/from Json file. Includes
  *          JsonParser to parse Member.
  *
  ******************************************************************************
  */

#ifndef MEMBERMANAGER_H
#define MEMBERMANAGER_H

#include <thread>
#include <mutex>
#include <map>
#include "../json/jsoncontainer.h"
#include "../json/jsonparser.h"

class MemberManager : public JsonContainer
{
public:
    MemberManager();
    ~MemberManager();
    std::unique_ptr<Member> GetMember(const QString &name);
    void RegisterNewMember(const Member &member) override;
    void SaveChangesOnMember(const Member &member) override;
    void DeleteMember(const QString &name) override;
    void MaintainExpiredSubscriptions();

private:
    JsonParser parser;
    QDate yesterday{QDate::currentDate()}; // to invoke MaintainExpiredSubscriptions at first run
    std::thread* subscription_maintain_thread;
    std::mutex members_array_mutex;
};

#endif // MEMBERMANAGER_H
