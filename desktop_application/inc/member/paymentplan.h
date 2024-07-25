#ifndef PAYMENTPLAN_H
#define PAYMENTPLAN_H

#include <QDate>
#include "payment.h"

class PaymentPlan
{
public:
    PaymentPlan() = default;
    PaymentPlan(int price, int num_of_installments, const QDate start_date);
    QJsonObject toJson() const;
    float OneInstallmentQuantity();
    int RemainingInstallmentQuantity();
    float RemainingPaymentsTotal();
    int GetNumOfInstallments();
    int GetPrice();

private:
    int price_;
    int num_of_installments_;
    std::vector<Payment> payment_plan;
};

#endif // PAYMENTPLAN_H
