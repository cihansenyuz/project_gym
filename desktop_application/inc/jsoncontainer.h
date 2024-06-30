#ifndef JSONCONTAINER_H
#define JSONCONTAINER_H

#include <QJsonArray>
#include <QJsonDocument>
#include <QFile>

class JsonContainer
{
public:
    JsonContainer();
    virtual void RegisterNewMember(const Member &member) = 0;
    virtual void SaveChangesOnMember() = 0;
    virtual void DeleteMember() = 0;

    bool SaveToFile();

private:
    QJsonArray members_array;
    QString file_path{"../../members.json"};
};

#endif // JSONCONTAINER_H
