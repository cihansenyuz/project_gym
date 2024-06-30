#ifndef JSONPARSER_H
#define JSONPARSER_H

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>

#include "member.h"

class JsonParser
{
public:
    JsonParser();
    Member* fromJsonArray(QJsonObject &member_json);
    Member* GetParsedMember(const QString &name);

private:
    void ParseMeasurements(Member *member, const QJsonArray &measurements_array);
    void ParseSubscriptions(Member *member, const QJsonArray &subscriptions_array);
    void ParseWeeklyExercisePlan(Member *member, const QJsonObject &weekly_exercise_plan_json);
    void ParseArchivedWeeklyExercisePlans(Member *member, const QJsonArray &archived_weekly_exercise_plans_array);
    Exercise* ParseExercise(const QJsonObject &exercise_json);

    Member* parsed_member{nullptr};
};

#endif // JSONPARSER_H
