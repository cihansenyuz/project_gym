#ifndef SUBSCRIPTION_H
#define SUBSCRIPTION_H

#include <QDate>
#include <QJsonObject>

class Subscription
{
public:
    Subscription() = default;
    Subscription(const QDate &start_date, const QDate &end_date, bool status);
    void SetSubscriptionPeriod(const QDate &start_date, const QDate &end_date);
    void ExtendSubscriptionEndDate(const QDate &end_date);
    void EndSubscription();
    bool HasSubscription() const;
    QDate GetSubscriptionStartDate() const;
    QDate GetSubscriptionEndDate() const;
    QJsonObject toJson() const;

private:
    QDate start_date_;
    QDate end_date_;
    bool status_{false};
    //int price_;
};

#endif // SUBSCRIPTION_H
