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
    void DoNextPayment();

    int GetTotalPayment() const;
    int GetInstallments() const;
    float GetPaymentQuantity() const;
    float GetRemainingPaymentQuantity() const;
    int GetRemainingInstallments() const;
    std::map<std::pair<QDate, float>, bool> GetPaymentPlan() const;
    void SetTotalPayment(const int total_payment);
    void SetInstallments(const int installments);
    void SetRemainingPaymentQuantity(int remaining_payment);
    void SetRemainingInstallments(int remaining_installments);
    void SetPaymentPlan(const std::map<std::pair<QDate, float>, bool> payment_plan);

private:
    int total_payment_;
    int installments_;
    float one_installment;
    float remaining_payment_;
    int remaining_installments_;
    std::map<std::pair<QDate, float>, bool> payment_plan_;
};

#endif // PAYMENT_H
