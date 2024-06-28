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
}

void MemberManager::RegisterNewMember(const Member &member){
    QJsonObject member_json = member.toJson();
    members_json.append(member_json);
    SaveToFile();
}

bool MemberManager::SetCurrentMemberByName(const QString &name) {
    for (int i = 0; i < members_json.size(); ++i) {
        QJsonObject member_json = members_json[i].toObject();
        if (member_json["name"].toString() == name) {
            current_member = fromJsonObject(member_json);
            return true;
        }
    }
    return false;

    return false; // member not found
}

Member* MemberManager::fromJsonObject(QJsonObject &member_json){
    Member *member_ptr = new Member();
    member_ptr->SetName(member_json["name"].toString());
    member_ptr->SetAge(member_json["age"].toInt());

    QJsonArray measurementsArray = member_json["measurements"].toArray();
    for (int i = 0; i < measurementsArray.size(); ++i) {
        QJsonObject measurement_json = measurementsArray[i].toObject();
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

    member_ptr->SetSubscriptionPeriod(QDate::fromString(member_json["subscription_start_date"].toString(), Qt::ISODate),
                                      QDate::fromString(member_json["subscription_end_date"].toString(), Qt::ISODate));

    QJsonArray subscriptions_array = member_json["archived_subscriptions"].toArray();
    for (int i = 0; i < subscriptions_array.size(); ++i) {
        QJsonObject subscription_json = subscriptions_array[i].toObject();
        Subscription archived_subscription(QDate::fromString(subscription_json["subscription_start_date"].toString(), Qt::ISODate),
                                         QDate::fromString(subscription_json["subscription_end_date"].toString(), Qt::ISODate),
                                         subscription_json["subscription"].toBool());
        member_ptr->AddSubscriptionToArchive(archived_subscription);
    }

    if (member_json.contains("exercise_plan")) {
        QJsonObject exercise_plan_json = member_json["exercise_plan"].toObject();
        member_ptr->SetWeeklyExercisePlanPeriod(QDate::fromString(exercise_plan_json["end_day"].toString(), Qt::ISODate),
                                             QDate::fromString(exercise_plan_json["start_day"].toString(), Qt::ISODate));

        QJsonArray current_weekly_plan_array = exercise_plan_json["weekly_exercise_plan"].toArray();
        std::vector<DailyExercisePlan> current_weekly_exercises;

        for (int i = 0; i < current_weekly_plan_array.size(); ++i){
            QJsonObject current_daily_exercise_json = current_weekly_plan_array[i].toObject();

            std::vector<Exercise*> current_daily_exercises;
            DailyExercisePlan current_daily_exercise;
            current_daily_exercise.SetCooldownPeriod(current_daily_exercise_json["cooldown_period"].toInt());

            QJsonArray current_daily_plan_array = current_daily_exercise_json["daily_exercise"].toArray();
            for (int j = 0; j < current_daily_plan_array.size(); ++j){
                QJsonObject current_daily_plan_json = current_daily_plan_array[i].toObject();
                if(Exercise::fromStringToExerciseType(current_daily_plan_json["type"].toString()) == ExerciseType::Cardio){
                    CardioWorkout *current_exercise = new CardioWorkout(Exercise::fromStringToExerciseType(current_daily_plan_json["type"].toString()),
                                                   Exercise::fromStringToExerciseName(current_daily_plan_json["name"].toString()),
                                                   current_daily_plan_json["durition"].toInt());
                    current_daily_exercises.push_back(current_exercise);
                }
                else{
                    StrengthWorkout *current_exercise = new StrengthWorkout(Exercise::fromStringToExerciseType(current_daily_plan_json["type"].toString()),
                                                     Exercise::fromStringToExerciseName(current_daily_plan_json["name"].toString()),
                                                     current_daily_plan_json["set"].toInt(),
                                                     current_daily_plan_json["repeat"].toInt());
                    current_daily_exercises.push_back(current_exercise);
                }
            }
            current_daily_exercise.SetDailyExecisePlan(current_daily_exercises);
            current_weekly_exercises.push_back(current_daily_exercise);
        }
        member_ptr->SetWeeklyExercisePlan(current_weekly_exercises);
    }

    QJsonObject exercise_plan_json = member_json["archived_exercise_plans"].toObject();
    WeeklyExercisePlan archivedWeeklyExercisePlan;
    archivedWeeklyExercisePlan.SetWeeklyExercisePlanPeriod(QDate::fromString(exercise_plan_json["end_day"].toString(), Qt::ISODate),
                                            QDate::fromString(exercise_plan_json["start_day"].toString(), Qt::ISODate));

    QJsonArray weekly_plan_array = exercise_plan_json["weekly_exercise_plan"].toArray();
    std::vector<DailyExercisePlan> weekly_exercises;

    for (int i = 0; i < weekly_plan_array.size(); ++i){
        QJsonObject daily_exercise_json = weekly_plan_array[i].toObject();

        std::vector<Exercise*> daily_exercises;
        DailyExercisePlan daily_exercise;
        daily_exercise.SetCooldownPeriod(daily_exercise_json["cooldown_period"].toInt());

        QJsonArray daily_plan_array = daily_exercise_json["daily_exercise"].toArray();
        for (int j = 0; j < daily_plan_array.size(); ++j){
            QJsonObject daily_plan_json = daily_plan_array[i].toObject();
            if(Exercise::fromStringToExerciseType(daily_plan_json["type"].toString()) == ExerciseType::Cardio){
                CardioWorkout *exercise = new CardioWorkout(Exercise::fromStringToExerciseType(daily_plan_json["type"].toString()),
                                               Exercise::fromStringToExerciseName(daily_plan_json["name"].toString()),
                                               daily_plan_json["durition"].toInt());
                daily_exercises.push_back(exercise);
            }
            else{
                StrengthWorkout *exercise = new StrengthWorkout(Exercise::fromStringToExerciseType(daily_plan_json["type"].toString()),
                                                 Exercise::fromStringToExerciseName(daily_plan_json["name"].toString()),
                                                 daily_plan_json["set"].toInt(),
                                                 daily_plan_json["repeat"].toInt());
                daily_exercises.push_back(exercise);
            }
        }
        daily_exercise.SetDailyExecisePlan(daily_exercises);
        weekly_exercises.push_back(daily_exercise);
    }
    archivedWeeklyExercisePlan.SetWeeklyExercisePlan(weekly_exercises);
    member_ptr->AddExercisePlanToArchive(archivedWeeklyExercisePlan);

    return member_ptr;
}

Member* MemberManager::GetCurrentMember() const{
    return current_member;
}

void MemberManager::SaveChangesOnCurrentMember(){
    for (int i = 0; i < members_json.size(); ++i) {
        QJsonObject member_json = members_json[i].toObject();
        if (member_json["name"].toString() == current_member->GetName()) {
            members_json[i] = QJsonValue(current_member->toJson());
        }
    }
    SaveToFile();
}

bool MemberManager::SaveToFile(){
    QJsonDocument document(members_json);
    QFile file(file_path);
    if (!file.open(QIODevice::WriteOnly)) {
        qDebug() << "Failed to open file for writing:" << file.errorString();
        return false;
    }

    file.write(document.toJson());
    file.close();
    return true;
}

void MemberManager::DeleteCurrentMember(){
    for (int i = 0; i < members_json.size(); ++i) {
        QJsonObject member_json = members_json[i].toObject();
        if (member_json["name"].toString() == current_member->GetName()) {
            members_json.removeAt(i);
        }
    }
    SaveToFile();
}
