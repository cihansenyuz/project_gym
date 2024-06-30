#include "../inc/jsonparser.h"

JsonParser::JsonParser() {}

Member* JsonParser::fromJsonObject(QJsonObject &member_json){
    Member *member_ptr = new Member();
    member_ptr->SetName(member_json["name"].toString());
    member_ptr->SetAge(member_json["age"].toInt());

    ParseMeasurements(member_ptr, member_json["measurements"].toArray());

    member_ptr->SetSubscriptionPeriod(QDate::fromString(member_json["subscription_start_date"].toString(), Qt::ISODate),
                                      QDate::fromString(member_json["subscription_end_date"].toString(), Qt::ISODate));
    ParseSubscriptions(member_ptr, member_json["archived_subscriptions"].toArray());

    if (member_json.contains("exercise_plan")) {
        ParseWeeklyExercisePlan(member_ptr, member_json["exercise_plan"].toObject());
    }

    QJsonObject exercise_plan_json = member_json["archived_exercise_plans"].toObject();
    ParseArchivedWeeklyExercisePlans(member_ptr, exercise_plan_json["archived_exercise_plans"].toArray());

    return member_ptr;
}

void JsonParser::ParseMeasurements(Member *member, const QJsonArray &measurements_array){
    for (int i = 0; i < measurements_array.size(); ++i) {
        QJsonObject measurement_json = measurements_array[i].toObject();
        Measurement recorded_measurement(QDate::fromString(measurement_json["taken_date"].toString(), Qt::ISODate),
                                         measurement_json["weight"].toDouble(),
                                         measurement_json["shoulder"].toDouble(),
                                         measurement_json["chest"].toDouble(),
                                         measurement_json["arm"].toDouble(),
                                         measurement_json["belly"].toDouble(),
                                         measurement_json["hip"].toDouble(),
                                         measurement_json["leg"].toDouble());
        member->AddMeasurement(recorded_measurement);
    }
}

void JsonParser::ParseSubscriptions(Member *member, const QJsonArray &subscriptions_array) {
    for (int i = 0; i < subscriptions_array.size(); ++i) {
        QJsonObject subscription_json = subscriptions_array[i].toObject();
        Subscription archived_subscription(
            QDate::fromString(subscription_json["subscription_start_date"].toString(), Qt::ISODate),
            QDate::fromString(subscription_json["subscription_end_date"].toString(), Qt::ISODate),
            subscription_json["subscription"].toBool()
            );
        member->AddSubscriptionToArchive(archived_subscription);
    }
}

void JsonParser::ParseWeeklyExercisePlan(Member *member, const QJsonObject &weekly_exercise_plan_json){
    std::vector<DailyExercisePlan> current_weekly_exercises;
    member->SetWeeklyExercisePlanPeriod(QDate::fromString(weekly_exercise_plan_json["start_date"].toString(), Qt::ISODate),
                                        QDate::fromString(weekly_exercise_plan_json["end_date"].toString(), Qt::ISODate));

    QJsonArray daily_exercise_plan_array = weekly_exercise_plan_json["weekly_exercise_plan"].toArray();
    for (int k = 0; k < daily_exercise_plan_array.size(); ++k){
        QJsonObject current_daily_exercise_json = daily_exercise_plan_array[k].toObject();

        std::vector<Exercise*> current_daily_exercises;
        DailyExercisePlan current_daily_exercise;
        current_daily_exercise.SetCooldownPeriod(current_daily_exercise_json["cooldown_period"].toInt());

        QJsonArray current_daily_plan_array = current_daily_exercise_json["daily_exercise"].toArray();
        for (int j = 0; j < current_daily_plan_array.size(); ++j){
            current_daily_exercises.push_back(ParseExercise(current_daily_plan_array[j].toObject()));
        }
        current_daily_exercise.SetDailyExecisePlan(current_daily_exercises);
        current_weekly_exercises.push_back(current_daily_exercise);
    }
    member->SetWeeklyExercisePlan(current_weekly_exercises);
}

void JsonParser::ParseArchivedWeeklyExercisePlans(Member *member, const QJsonArray &archived_weekly_exercise_plans_array){
    for (int i = 0; i < archived_weekly_exercise_plans_array.size(); ++i){
        QJsonObject weekly_exercise_plan_json = archived_weekly_exercise_plans_array[i].toObject();
        std::vector<DailyExercisePlan> weekly_exercise_plan;
        WeeklyExercisePlan archivedWeeklyExercisePlan;
        archivedWeeklyExercisePlan.SetWeeklyExercisePlanPeriod(QDate::fromString(weekly_exercise_plan_json["end_day"].toString(), Qt::ISODate),
                                                               QDate::fromString(weekly_exercise_plan_json["start_day"].toString(), Qt::ISODate));

        ////////////////////////////////  WeeklyExercisePlan parsing /////////////////////////////////////////////
        QJsonArray daily_exercise_plan_array = weekly_exercise_plan_json["weekly_exercise_plan"].toArray();
        for(int k = 0; k < daily_exercise_plan_array.size(); ++k){
            QJsonObject daily_exercise_plan_json = daily_exercise_plan_array[i].toObject();
            std::vector<Exercise*> daily_exercise_plan;
            DailyExercisePlan daily_exercise;
            daily_exercise.SetCooldownPeriod(daily_exercise_plan_json["cooldown_period"].toInt());

            ////////////////////////////////  DailyExercisePlan parsing /////////////////////////////////////////////
            QJsonArray daily_exercise_plan_array = daily_exercise_plan_json["daily_exercise"].toArray();
            for (int j = 0; j < daily_exercise_plan_array.size(); ++j){
                daily_exercise_plan.push_back(ParseExercise(daily_exercise_plan_array[i].toObject()));
            }
            daily_exercise.SetDailyExecisePlan(daily_exercise_plan);
            weekly_exercise_plan.push_back(daily_exercise);
        }
        archivedWeeklyExercisePlan.SetWeeklyExercisePlan(weekly_exercise_plan);
        member->AddExercisePlanToArchive(archivedWeeklyExercisePlan);
    }
}

Exercise* JsonParser::ParseExercise(const QJsonObject &exercise_json){
    ExerciseType type = Exercise::fromStringToExerciseType(exercise_json["type"].toString());

    if(type == ExerciseType::Cardio){
        return new CardioWorkout(type,
                                 Exercise::fromStringToExerciseName(exercise_json["name"].toString()),
                                 exercise_json["durition"].toInt());
    } else {
        return new StrengthWorkout(type,
                                   Exercise::fromStringToExerciseName(exercise_json["name"].toString()),
                                   exercise_json["set"].toInt(),
                                   exercise_json["repeat"].toInt());
    }
}

Member* JsonParser::GetParsedMember(const QString &name){
    for (int i = 0; i < members_json.size(); ++i) {
        QJsonObject member_json = members_json[i].toObject();
        if (member_json["name"].toString() == name) {
            parsed_member = fromJsonObject(member_json);
            return parsed_member;
        }
    }
    parsed_member = nullptr;
    return parsed_member;
}
