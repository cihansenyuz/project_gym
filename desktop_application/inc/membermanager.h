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
    void RegisterNewMember(Member &new_member);
    void SaveMemberToJson(const Member &member);
    // unsubscribe a member
    // start subscription of a member
    // get/find a member
    // delete a member

private:
    QJsonArray members_json;
    QString file_path{"../../members.json"};
};

#endif // MEMBERMANAGER_H
