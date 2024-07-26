#ifndef PAYMENT_H
#define PAYMENT_H

#include <QDate>
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
