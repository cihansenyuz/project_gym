#include "../../inc/json/jsoncontainer.h"

bool JsonContainer::SaveToFile(){
    QJsonDocument document(members_array);
    QFile file(file_path);
    if (!file.open(QIODevice::WriteOnly)) {
        qDebug() << "Failed to open file for writing:" << file.errorString();
        return false;
    }

    file.write(document.toJson());
    qDebug() << "Written to the file";
    file.close();
    return true;
}

void JsonContainer::LoadFromFile(){
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

    members_array = json_document.array();
    qDebug() << "JSON file loaded";
}

QJsonArray* JsonContainer::GetMemberArrayData(){
    return &members_array;
}

void JsonContainer::SetMemberArrayData(const std::unique_ptr<QJsonArray> &fetched){
    QJsonArray empty;
    members_array = empty;
    members_array = *fetched;
    if(members_array.isEmpty())
        qDebug() << "recieved fetched array is empty";
}
