#ifndef JSONPARSER_H
#define JSONPARSER_H

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>

#include "member.h"
#include "cardioworkout.h"
#include "strengthworkout.h"

class JsonParser
{
public:
    JsonParser();
    Member* fromJsonObject(QJsonObject &member_json);
    virtual Member* GetMember(const QString &name){return nullptr;}

private:
    void ParseMeasurements(Member *member, const QJsonArray &measurements_array);
    void ParseSubscriptions(Member *member, const QJsonArray &subscriptions_array);
    void ParseWeeklyExercisePlan(Member *member, const QJsonObject &weekly_exercise_plan_json);
    void ParseArchivedWeeklyExercisePlans(Member *member, const QJsonArray &archived_weekly_exercise_plans_array);
    Exercise* ParseExercise(const QJsonObject &exercise_json);
};

#endif // JSONPARSER_H
