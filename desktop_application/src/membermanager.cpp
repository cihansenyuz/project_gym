#include "../inc/membermanager.h"

MemberManager::MemberManager() {
    QFile file(file_path);
    if (!file.exists()) {
        qWarning() << "File does not exist:" << file_path;
        return;
    }

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Couldn't open file:" << file_path;
        qWarning() << "Error:" << file.errorString();
        return;
    }

    QByteArray jsonData = file.readAll();
    file.close();

    QJsonDocument json_document = QJsonDocument::fromJson(jsonData);
    if (json_document.isNull() || !json_document.isArray()) {
        qWarning() << "Invalid JSON format";
    }

    members_json = json_document.array();
    for(const QJsonValue &value : members_json){
        QJsonObject member = value.toObject();
        qDebug() << member["name"].toString();

        for(const QJsonValue &value : member["measurements"].toArray()){
            QJsonObject measurement = value.toObject();
            qDebug() << measurement["arm"].toDouble();
        }
    }
}

void MemberManager::RegisterNewMember(Member &new_member){
    // do implemantation of registering in a json file.

}

void MemberManager::SaveMemberToJson(const Member &member){
    QJsonObject member_json = member.toJson();
    members_json.append(member_json);
    QJsonDocument document(members_json);

    QFile file(file_path);
    if (!file.open(QIODevice::WriteOnly)) {
        qDebug() << "Failed to open file for writing:" << file.errorString();
        return;
    }

    file.write(document.toJson());
    file.close();
}
