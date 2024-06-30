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

    bool SaveToFile();

    QJsonArray members_array;

private:
    QString file_path{"../../members.json"};
};

#endif // JSONCONTAINER_H
