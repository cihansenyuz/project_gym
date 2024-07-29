#include "../../inc/member/paymentplan.h"

PaymentPlan::PaymentPlan(int price, int num_of_installments, const QDate start_date)
    : price_(price), num_of_installments_(num_of_installments) {

    float payment_quantity = price / num_of_installments;
    do{
        payment_plan_.push_back(Payment(payment_quantity,
                                       start_date.addMonths(--num_of_installments)));
    }while(num_of_installments);
}

float PaymentPlan::OneInstallmentQuantity() const { return payment_plan_.back().GetQuantity(); }
int PaymentPlan::GetNumOfInstallments() const { return num_of_installments_; }
int PaymentPlan::GetPrice() const { return price_; }
std::vector<Payment> PaymentPlan::GetPaymentsList() const { return payment_plan_; }

void PaymentPlan::ReplaceDefaultPayments(const std::vector<Payment> &updated_payments){
    payment_plan_ = updated_payments;
}

void PaymentPlan::SetPaymentPlan(const PaymentPlan &payment_plan){
    this->price_ = payment_plan.GetPrice();
    this->num_of_installments_ = payment_plan.GetNumOfInstallments();
    this->payment_plan_ = payment_plan.GetPaymentsList();
}

int PaymentPlan::RemainingInstallmentQuantity() const{
    int remaining = 0;
    for(auto &payment : payment_plan_)
        if(!payment.IsPaid())
            remaining++;
    return remaining;
}

float PaymentPlan::RemainingPaymentsTotal() const{
    float remaining = 0;
    for(auto &payment : payment_plan_)
        if(!payment.IsPaid())
            remaining += payment.GetQuantity();
    return remaining;
}

void PaymentPlan::Pay(){
    for(auto &payment : payment_plan_)
        if(!payment.IsPaid()){
            payment.MakePaid();
            return;
        }
}

QJsonObject PaymentPlan::toJson() const{
    QJsonObject json;
    json["price"] = price_;
    json["num_of_installments"] = num_of_installments_;

    QJsonArray json_arr;
    for(auto &payment : payment_plan_)
        json_arr.append(payment.toJson());

    json["payments"] = json_arr;
    return json;
}
