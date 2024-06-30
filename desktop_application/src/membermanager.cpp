#include "../inc/membermanager.h"

Member* MemberManager::GetMember(const QString &name){
    for (int i = 0; i < members_array.size(); ++i) {
        QJsonObject member_json = members_array[i].toObject();
        if (member_json["name"].toString() == name) {
            return fromJsonObject(member_json);
        }
    }
    return nullptr;
}

void MemberManager::RegisterNewMember(const Member &member){
    QJsonObject member_json = member.toJson();
    members_array.append(member_json);
    SaveToFile();
}

void MemberManager::SaveChangesOnMember(const Member &member){
    for (int i = 0; i < members_array.size(); ++i) {
        QJsonObject member_json = members_array[i].toObject();
        if (member_json["name"].toString() == member.GetName()) {
            members_array[i] = QJsonValue(member.toJson());
        }
    }
    SaveToFile();
}

void MemberManager::DeleteMember(const QString &name){
    for (int i = 0; i < members_array.size(); ++i) {
        QJsonObject member_json = members_array[i].toObject();
        if (member_json["name"].toString() == name) {
            members_array.removeAt(i);
        }
    }
    SaveToFile();
}
