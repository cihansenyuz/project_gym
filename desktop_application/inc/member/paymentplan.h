/**
  ******************************************************************************
  * @file    paymentplan.hpp
  * @author  Cihan Senyuz
  * @date    26.07.2024
  * @brief   Header for PaymentPlan class.
  *          This file contains the definition of the PaymentPlan class, which
  *          represents a payment plan with a specified price, number of installments,
  *          and a list of payments. The class includes methods for managing payments
  *          and calculating remaining installments and payments.
  *
  ******************************************************************************
  */

#ifndef PAYMENTPLAN_H
#define PAYMENTPLAN_H

#include <QJsonArray>
#include "payment.h"

class PaymentPlan
{
public:
    PaymentPlan() = default;
    PaymentPlan(int price, int num_of_installments, const QDate start_date);
    QJsonObject toJson() const;
    float OneInstallmentQuantity() const;
    int RemainingInstallmentQuantity() const;
    float RemainingPaymentsTotal() const;
    void ReplaceDefaultPayments(const std::vector<Payment> &updated_payments);
    void Pay();

    int GetNumOfInstallments() const;
    int GetPrice() const;
    std::vector<Payment> GetPaymentsList() const;
    void SetPaymentPlan(const PaymentPlan &payment_plan);

private:
    int price_;
    int num_of_installments_;
    std::vector<Payment> payment_plan_;
};

#endif // PAYMENTPLAN_H
