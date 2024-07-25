#ifndef PAYMENT_H
#define PAYMENT_H

#include <map>
#include <QDate>
#include <QJsonObject>
#include <QJsonArray>

class Payment
{
public:
    Payment() = default;
    Payment(int total_payment, int installments, QDate start_date);
    QJsonObject toJson() const;
    std::pair<QDate, float> NextPaymentInfo();
    int GetTotalPayment() const;
    int GetInstallments() const;
    std::map<std::pair<QDate, float>, bool> GetPaymentPlan() const;
    void SetTotalPayment(const int total_payment);
    void SetInstallments(const int installments);
    void SetPaymentPlan(const std::map<std::pair<QDate, float>, bool> payment_plan);

private:
    int total_payment_;
    int installments_;
    std::map<std::pair<QDate, float>, bool> payment_plan_;
};

#endif // PAYMENT_H
