#include "../../inc/member/payment.h"

Payment::Payment(float quantity, QDate due_date)
    : quantity_(quantity), due_date_(due_date) {}

void Payment::Pay() { paid = true; }
float Payment::GetQuantity() { return quantity_; }
bool Payment::IsPaid() { return paid; }

QJsonObject Payment::toJson() const{
    QJsonObject json;
    json["quantity"] = quantity_;
    json["due_date"] = due_date_.toString(Qt::ISODate);
    json["paid"] = paid;

    return json;
}
