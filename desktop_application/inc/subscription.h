/**
  ******************************************************************************
  * @file    subscription.hpp
  * @author  Cihan Senyuz
  * @date    23.06.2024
  * @brief   Header for subscription.cpp file.
  *                 Manages subscriptions for members, including start and end dates,
  *          and handles archived subscriptions.Provides methods for adding,
  *          updating, and retrieving subscription information.
  *
  ******************************************************************************
  */

#ifndef SUBSCRIPTION_H
#define SUBSCRIPTION_H

#include <QDate>
#include <QJsonObject>

class Subscription
{
public:
    Subscription() = default; // no use
    Subscription(const QDate &start_date, const QDate &end_date, bool status);
    void SetSubscriptionPeriod(const QDate &start_date, const QDate &end_date);
    void ExtendSubscriptionEndDate(const QDate &end_date);
    void EndSubscription(bool update_end_date = true);
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
