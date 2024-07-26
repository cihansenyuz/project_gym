/**
  ******************************************************************************
  * @file    payment.hpp
  * @author  Cihan Senyuz
  * @date    26.07.2024
  * @brief   Header for Payment class.
  *          This file contains the definition of the Payment class, which
  *          represents a payment with a specified quantity, due date, and
  *          payment status. The class includes methods to convert to JSON and
  *          update the payment status.
  *
  ******************************************************************************
  */

#ifndef PAYMENT_H
#define PAYMENT_H

#include <QJsonObject>

class Payment
{
public:
    Payment(float quantity, const QDate due_date, bool is_paid = false);
    QJsonObject toJson() const;
    void MakePaid();

    float GetQuantity() const;
    QDate GetDueDate() const;
    bool IsPaid() const;

private:
    float quantity_;
    QDate due_date_;
    bool paid;
};

#endif // PAYMENT_H
