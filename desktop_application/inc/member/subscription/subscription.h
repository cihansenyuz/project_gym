/**
  ******************************************************************************
  * @file    subscription.hpp
  * @author  Cihan Senyuz
  * @date    23.06.2024
  * @brief   Header for subscription.cpp file.
  *                 Manages subscriptions for members, including start and end dates,
  *          and handles archived subscriptions. Provides methods for adding,
  *          updating, and retrieving subscription information. Inherets PaymentPlan
  *          to manage payments of the subscription.
  *
  ******************************************************************************
  */

#ifndef SUBSCRIPTION_H
#define SUBSCRIPTION_H

#include "paymentplan.h"

class Subscription : public PaymentPlan
{
public:
    Subscription() = default;
    Subscription(const QDate &start_date, const QDate &end_date, bool status);
    void SetSubscriptionPeriod(const QDate &start_date, const QDate &end_date);
    void ExtendSubscriptionEndDate(const QDate &end_date);
    void EndSubscription(bool update_end_date);
    bool HasSubscription() const;
    QDate GetSubscriptionStartDate() const;
    QDate GetSubscriptionEndDate() const;
    QJsonObject toJson(bool is_archived = false) const;

private:
    QDate start_date_;
    QDate end_date_;
    bool status_{false};
};

#endif // SUBSCRIPTION_H
