#include "../../../inc/member/subscription/subscription.h"

Subscription::Subscription(const QDate &start_date, const QDate &end_date, bool status)
    : start_date_(start_date), end_date_(end_date), status_(status) {}

void Subscription::SetSubscriptionPeriod(const QDate &start_date, const QDate &end_date){
    start_date_ = start_date;
    end_date_ = end_date;
    if(end_date >= QDate::currentDate())
        status_ = true;
}

void Subscription::ExtendSubscriptionEndDate(const QDate &end_date){
    end_date_ = end_date;
}

void Subscription::EndSubscription(bool update_end_date){
    status_ = false;
    if(update_end_date)
        end_date_ = QDate::currentDate();
}

bool Subscription::HasSubscription() const { return status_; }
QDate Subscription::GetSubscriptionStartDate() const { return start_date_; }
QDate Subscription::GetSubscriptionEndDate() const { return end_date_; }

QJsonObject Subscription::toJson(bool is_archived) const {
    QJsonObject json;
    json["subscription_start_date"] = start_date_.toString(Qt::ISODate);
    json["subscription_end_date"] = end_date_.toString(Qt::ISODate);
    if(!is_archived){
        json["status"] = status_;
        json["payment_plan"] = PaymentPlan::toJson();
    }
    return json;
}
