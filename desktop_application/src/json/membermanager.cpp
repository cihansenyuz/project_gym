#include "../../inc/json/membermanager.h"

MemberManager::MemberManager() {
    auto IsNextDay = [this](){
        while(true){
            if(QDate::currentDate() >= yesterday){
                yesterday = QDate::currentDate();
                MaintainExpiredSubscriptions();
            }
            std::this_thread::sleep_for(std::chrono::hours(12));
        }
    };
    subscription_maintain_thread = new std::thread(IsNextDay);
    subscription_maintain_thread->detach();
}

MemberManager::~MemberManager(){
    if (subscription_maintain_thread->joinable()) {
        subscription_maintain_thread->join();
    }
    delete subscription_maintain_thread;
}

std::unique_ptr<Member> MemberManager::GetMember(const QString &name){
    std::lock_guard<std::mutex> lock(members_array_mutex);
    for (int i = 0; i < members_array.size(); ++i) {
        QJsonObject member_json = members_array[i].toObject();

        if (member_json["name"].toString() == name) {
            return std::move(parser.ParseMemberFromJson(member_json));
        }
    }
    return nullptr;
}

void MemberManager::RegisterNewMember(const Member &member){
    std::lock_guard<std::mutex> lock(members_array_mutex);
    QJsonObject member_json = member.toJson();
    members_array.append(member_json);
    SaveToFile();
}

void MemberManager::SaveChangesOnMember(const Member &member){
    std::lock_guard<std::mutex> lock(members_array_mutex);
    for (int i = 0; i < members_array.size(); ++i) {
        QJsonObject member_json = members_array[i].toObject();

        if (member_json["name"].toString() == member.GetName()) {
            members_array[i] = QJsonValue(member.toJson());
        }
    }
    SaveToFile();
}

void MemberManager::DeleteMember(const QString &name){
    std::lock_guard<std::mutex> lock(members_array_mutex);
    for (int i = 0; i < members_array.size(); ++i) {
        QJsonObject member_json = members_array[i].toObject();

        if (member_json["name"].toString() == name) {
            members_array.removeAt(i);
        }
    }
    SaveToFile();
}

void MemberManager::MaintainExpiredSubscriptions(){
    std::lock_guard<std::mutex> lock(members_array_mutex);
    bool has_changes = false;

    for (int i = 0; i < members_array.size(); ++i) {
        QJsonObject member_json = members_array[i].toObject();

        if (member_json["subscription"].toBool() == true) {
            if (QDate::fromString(member_json["subscription_end_date"].toString(), Qt::ISODate) < QDate::currentDate()){
                std::unique_ptr<Member> member_to_be_updated = parser.ParseMemberFromJson(member_json);
                member_to_be_updated->EndSubscription(false);
                members_array[i] = member_to_be_updated->toJson();
                has_changes = true;
            }
        }
    }
    if(has_changes)
        SaveToFile();
}
