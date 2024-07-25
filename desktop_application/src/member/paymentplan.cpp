#include "../../inc/member/paymentplan.h"

PaymentPlan::PaymentPlan(int price, int num_of_installments, const QDate start_date)
    : price_(price), num_of_installments_(num_of_installments) {

    float payment_quantity = price / num_of_installments;
    do{
        payment_plan.push_back(Payment(payment_quantity,
                                       start_date.addMonths(--num_of_installments)));
    }while(num_of_installments);
}

float PaymentPlan::OneInstallmentQuantity() { return payment_plan.end()->GetQuantity(); }
int PaymentPlan::GetNumOfInstallments() { return num_of_installments_; }
int PaymentPlan::GetPrice() { return price_; }

int PaymentPlan::RemainingInstallmentQuantity(){
    int remaining = 0;
    for(auto &payment : payment_plan)
        if(payment.IsPaid())
            remaining++;
    return remaining;
}

float PaymentPlan::RemainingPaymentsTotal(){
    float remaining = 0;
    for(auto &payment : payment_plan)
        if(!payment.IsPaid())
            remaining += payment.GetQuantity();
    return remaining;
}

QJsonObject PaymentPlan::toJson() const{

}
