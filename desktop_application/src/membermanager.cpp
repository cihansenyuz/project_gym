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
    /*for(const QJsonValue &value : members_json){
        QJsonObject member = value.toObject();
        qDebug() << member["name"].toString();

        for(const QJsonValue &value : member["measurements"].toArray()){
            QJsonObject measurement = value.toObject();
            qDebug() << measurement["arm"].toDouble();
        }
    }*/
}

void MemberManager::RegisterNewMember(const Member &new_member){
    SaveMemberToJson(new_member);
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

bool MemberManager::GetMemberByName(const QString &name) {
    for(const QJsonValue &value : members_json) {
        QJsonObject member_json = value.toObject();
        if (member_json["name"].toString() == name){
            current_member = fromJsonObject(member_json);
            return true;
        }
    }
    return false; // member not found
}

Member* MemberManager::fromJsonObject(QJsonObject &member_json){
    Member *member_ptr = new Member();
    member_ptr->SetName(member_json["name"].toString());
    member_ptr->SetAge(member_json["age"].toInt());
    member_ptr->SetSubscriptionPeriod(QDate::fromString(member_json["subscription_start_date"].toString(), Qt::ISODate),
                                      QDate::fromString(member_json["subscription_end_date"].toString(), Qt::ISODate));

    for(const QJsonValue &value : member_json["measurements"].toArray()){
        QJsonObject measurement_json = value.toObject();
        Measurement recorded_measurement(QDate::fromString(measurement_json["taken_date"].toString(), Qt::ISODate),
                                         measurement_json["weight"].toDouble(),
                                         measurement_json["shoulder"].toDouble(),
                                         measurement_json["chest"].toDouble(),
                                         measurement_json["arm"].toDouble(),
                                         measurement_json["belly"].toDouble(),
                                         measurement_json["hip"].toDouble(),
                                         measurement_json["leg"].toDouble());
        member_ptr->AddMeasurement(recorded_measurement);
    }
    return member_ptr;
}
