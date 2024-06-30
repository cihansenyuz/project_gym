/**
  ******************************************************************************
  * @file    jsonparser.h
  * @author  Cihan Senyuz
  * @date    30.06.2024
  * @brief   Header for jsonparser.cpp file.
  *                 Provides methods to parse JSON data into Member objects,
  *          including measurements, subscriptions, and exercise plans. Contains
  *          functions to parse various JSON structures and connvert them into
  *          appropriate objects.
  *
  ******************************************************************************
  */

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
    JsonParser() = default;
    Member* fromJsonObject(QJsonObject &member_json);
    virtual Member* GetMember(const QString &name) = 0;

private:
    void ParseMeasurements(Member *member, const QJsonArray &measurements_array);
    void ParseSubscriptions(Member *member, const QJsonArray &subscriptions_array);
    void ParseWeeklyExercisePlan(Member *member, const QJsonObject &weekly_exercise_plan_json);
    void ParseArchivedWeeklyExercisePlans(Member *member, const QJsonArray &archived_weekly_exercise_plans_array);
    Exercise* ParseExercise(const QJsonObject &exercise_json);
};

#endif // JSONPARSER_H
