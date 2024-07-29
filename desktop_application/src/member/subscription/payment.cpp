#include "../../../inc/member/subscription/payment.h"

Payment::Payment(float quantity, QDate due_date, bool is_paid)
    : quantity_(quantity), due_date_(due_date), paid(is_paid) {}

void Payment::MakePaid() { paid = true; }
float Payment::GetQuantity() const { return quantity_; }
QDate Payment::GetDueDate() const { return due_date_; }
bool Payment::IsPaid() const { return paid; }

QJsonObject Payment::toJson() const{
    QJsonObject json;
    json["quantity"] = quantity_;
    json["due_date"] = due_date_.toString(Qt::ISODate);
    json["paid"] = paid;

    return json;
}
