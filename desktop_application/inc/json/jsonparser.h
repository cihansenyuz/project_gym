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

#include "../member/member.h"

class JsonParser
{
public:
    JsonParser() = default;
    std::unique_ptr<Member> ParseMemberFromJson(QJsonObject &member_json);

private:
    void ParseMeasurements(const QJsonArray &measurements_array);
    void ParsePayments(const QJsonObject &payment_plan_json);
    void ParseSubscriptions(const QJsonArray &subscriptions_array);
    void ParseWeeklyExercisePlan(const QJsonObject &weekly_exercise_plan_json);
    void ParseArchivedWeeklyExercisePlans(const QJsonArray &archived_weekly_exercise_plans_array);
    Exercise* ParseExercise(const QJsonObject &exercise_json);

    std::unique_ptr<Member> member_to_be_parsed;
};

#endif // JSONPARSER_H
