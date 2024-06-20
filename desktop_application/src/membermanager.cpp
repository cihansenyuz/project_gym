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

    documented_members = QJsonDocument::fromJson(jsonData);
    if (documented_members.isNull() || !documented_members.isObject()) {
        qWarning() << "Invalid JSON format";
    }

}

void MemberManager::RegisterNewMember(Member &new_member){
    // do implemantation of registering in a json file.
}
