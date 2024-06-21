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
    void RegisterNewMember(const Member &new_member);
    void SaveMemberToJson(const Member &member);
    bool GetMemberByName(const QString &name);
    // unsubscribe a member
    // start subscription of a member
    // delete a member
    Member *current_member;

private:
    Member* fromJsonObject(QJsonObject &member_json);

    QJsonArray members_json;
    QString file_path{"../../members.json"};
};

#endif // MEMBERMANAGER_H
