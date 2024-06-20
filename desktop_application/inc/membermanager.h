#ifndef MEMBERMANAGER_H
#define MEMBERMANAGER_H

#include "member.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>

class MemberManager
{
public:
    MemberManager();
    void RegisterNewMember(Member &new_member);
    // unsubscribe a member
    // start subscription of a member
    // get/find a member
    // delete a member

private:
    QJsonDocument documented_member;
    QString file_path{"../../members.json"};
};

#endif // MEMBERMANAGER_H
