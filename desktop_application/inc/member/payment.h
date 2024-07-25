#ifndef PAYMENT_H
#define PAYMENT_H

#include <map>
#include <QDate>
#include <QJsonObject>
#include <QJsonArray>

class Payment
{
public:
    Payment(int total_payment, int installments, QDate start_date);
    QJsonObject toJson() const;
    std::pair<QDate, float> NextPaymentInfo();

private:
    int total_payment_;
    int installments_;
    std::map<std::pair<QDate, float>, bool> payment_plan_;
};

#endif // PAYMENT_H
