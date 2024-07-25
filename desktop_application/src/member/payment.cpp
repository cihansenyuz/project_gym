#include "../../inc/member/payment.h"

Payment::Payment(int total_payment, int installments, QDate start_date)
    : total_payment_(total_payment), installments_(installments) {

    float one_installment = total_payment / installments;
    do{
        payment_plan_[std::make_pair(start_date, one_installment)] = false;
        start_date = start_date.addMonths(1);
        installments--;
    }while(installments);
}

std::pair<QDate, float> Payment::NextPaymentInfo(){
    for(auto &payment : payment_plan_){
        if(!payment.second)
            return payment.first;
    }
    return std::make_pair(QDate(1,1,1900), 0.0);
}

QJsonObject Payment::toJson() const{
    QJsonObject json;
    json["total_payment"] = total_payment_;
    json["installments"] = installments_;

    QJsonArray jsonArray;
    for (const auto& payment : payment_plan_) {
        QJsonObject jsonPayment;
        jsonPayment["date"] = payment.first.first.toString(Qt::ISODate);
        jsonPayment["amount"] = payment.first.second;
        jsonPayment["is_paid"] = payment.second;
        jsonArray.append(jsonPayment);
    }

    json["payment_plan"] = jsonArray;
    return json;
}

int Payment::GetTotalPayment() const { return total_payment_; }
void Payment::SetTotalPayment(const int total_payment) { total_payment_ = total_payment; }
int Payment::GetInstallments() const { return installments_; }
void Payment::SetInstallments(const int installments) { installments_ = installments; }
std::map<std::pair<QDate, float>, bool> Payment::GetPaymentPlan() const { return payment_plan_; }
void Payment::SetPaymentPlan(const std::map<std::pair<QDate, float>, bool> payment_plan){
    payment_plan_ = payment_plan;
}
