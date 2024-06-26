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
        member_ptr->SetTargetDate(QDate::fromString(exercise_plan_json["end_day"].toString(), Qt::ISODate),
                                             QDate::fromString(exercise_plan_json["start_day"].toString(), Qt::ISODate));

        QJsonArray current_weekly_plan_array = exercise_plan_json["weekly_plan"].toArray();
        std::vector<Exercise::Exercise> current_exercises;
        for (int i = 0; i < current_weekly_plan_array.size(); ++i){
            QJsonObject current_exercise_json = current_weekly_plan_array[i].toObject();

            Exercise::Exercise current_exercise(Exercise::fromStringExerciseType(current_exercise_json["type"].toString()),
                                                Exercise::fromStringExerciseName(current_exercise_json["name"].toString()),
                                                current_exercise_json["set"].toInt(),
                                                current_exercise_json["repeat"].toInt(),
                                                current_exercise_json["cooldown_period"].toInt(),
                                                QDate::fromString(current_exercise_json["last_done_date"].toString(), Qt::ISODate));

            current_exercises.push_back(current_exercise);
        }
        member_ptr->SetWeeklyPlan(current_exercises);
    }

    QJsonArray exercise_plans_array = member_json["archived_exercise_plans"].toArray();
    for (int i = 0; i < exercise_plans_array.size(); ++i) {
        QJsonObject exercise_plan_json = exercise_plans_array[i].toObject();
        ExercisePlan archived_exercise_plan;
        archived_exercise_plan.SetTargetDate(QDate::fromString(exercise_plan_json["end_day"].toString(), Qt::ISODate),
                                            QDate::fromString(exercise_plan_json["start_day"].toString(), Qt::ISODate));

        QJsonArray weekly_plan_array = exercise_plan_json["weekly_plan"].toArray();
        std::vector<Exercise::Exercise> archived_exercises;
        for (int i = 0; i < weekly_plan_array.size(); ++i){
            QJsonObject exercise_json = weekly_plan_array[i].toObject();

            Exercise::Exercise exercise(Exercise::fromStringExerciseType(exercise_json["type"].toString()),
                                                Exercise::fromStringExerciseName(exercise_json["name"].toString()),
                                                exercise_json["set"].toInt(),
                                                exercise_json["repeat"].toInt(),
                                                exercise_json["cooldown_period"].toInt(),
                                        QDate::fromString(exercise_json["last_done_date"].toString(), Qt::ISODate));

            archived_exercises.push_back(exercise);
        }
        archived_exercise_plan.SetWeeklyPlan(archived_exercises);
        member_ptr->AddExercisePlanToArchive(archived_exercise_plan);
    }
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
