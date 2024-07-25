#ifndef PAYMENT_H
#define PAYMENT_H

#include <QDate>
#include <QJsonObject>

class Payment
{
public:
    Payment(float quantity, const QDate due_date);
    QJsonObject toJson() const;
    void Pay();

    float GetQuantity();
    bool IsPaid();

private:
    float quantity_;
    QDate due_date_;
    bool paid{false};
};

#endif // PAYMENT_H
