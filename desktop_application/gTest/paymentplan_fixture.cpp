#include <gtest/gtest.h>
#include <QDate>
#include <QDebug>
#include <QJsonObject>
#include <QJsonArray>
#include "../inc/member/paymentplan.h"
#include "../inc/member/payment.h"

class PaymentPlanTest : public ::testing::Test {
protected:
    void SetUp() override {
        price = 1200;
        num_of_installments = 12;
        start_date = QDate(2023, 1, 1);
        payment_plan = PaymentPlan(price, num_of_installments, start_date);
    }

    void TearDown() override {}

    int price;
    int num_of_installments;
    QDate start_date;
    PaymentPlan payment_plan;
};

TEST_F(PaymentPlanTest, Constructor) {
    EXPECT_EQ(payment_plan.GetPrice(), price);
    EXPECT_EQ(payment_plan.GetNumOfInstallments(), 12);

    auto payments = payment_plan.GetPaymentsList();
    EXPECT_EQ(payments.size(), num_of_installments);
    
    for (int i = 0; i < num_of_installments; ++i) {
        EXPECT_EQ(payments[i].GetDueDate(), start_date.addMonths(11-i));
        EXPECT_FLOAT_EQ(payments[i].GetQuantity(), price / num_of_installments);
        EXPECT_FALSE(payments[i].IsPaid());
    }
}

TEST_F(PaymentPlanTest, OneInstallmentQuantity) {
    EXPECT_FLOAT_EQ(payment_plan.OneInstallmentQuantity(), price / num_of_installments);
}

TEST_F(PaymentPlanTest, RemainingInstallmentQuantity) {
    EXPECT_EQ(payment_plan.RemainingInstallmentQuantity(), num_of_installments);

    payment_plan.Pay();
    EXPECT_EQ(payment_plan.RemainingInstallmentQuantity(), num_of_installments - 1);
}

TEST_F(PaymentPlanTest, RemainingPaymentsTotal) {
    EXPECT_FLOAT_EQ(payment_plan.RemainingPaymentsTotal(), price);

    payment_plan.Pay();
    EXPECT_FLOAT_EQ(payment_plan.RemainingPaymentsTotal(), price - (price / num_of_installments));
}

TEST_F(PaymentPlanTest, ReplaceDefaultPayments) {
    std::vector<Payment> new_payments;
    for (int i = 0; i < num_of_installments; ++i) {
        new_payments.push_back(Payment(100.0f, start_date.addMonths(i)));
    }

    payment_plan.ReplaceDefaultPayments(new_payments);
    auto payments = payment_plan.GetPaymentsList();

    for (int i = 0; i < num_of_installments; ++i) {
        EXPECT_EQ(payments[i].GetDueDate(), new_payments[i].GetDueDate());
        EXPECT_FLOAT_EQ(payments[i].GetQuantity(), new_payments[i].GetQuantity());
        EXPECT_EQ(payments[i].IsPaid(), new_payments[i].IsPaid());
    }
}

TEST_F(PaymentPlanTest, SetPaymentPlan) {
    PaymentPlan new_plan(2400, 24, QDate(2023, 6, 1));
    payment_plan.SetPaymentPlan(new_plan);

    EXPECT_EQ(payment_plan.GetPrice(), new_plan.GetPrice());
    EXPECT_EQ(payment_plan.GetNumOfInstallments(), new_plan.GetNumOfInstallments());

    auto new_payments = new_plan.GetPaymentsList();
    auto payments = payment_plan.GetPaymentsList();
    EXPECT_EQ(payments.size(), new_payments.size());

    for (size_t i = 0; i < payments.size(); ++i) {
        EXPECT_EQ(payments[i].GetDueDate(), new_payments[i].GetDueDate());
        EXPECT_FLOAT_EQ(payments[i].GetQuantity(), new_payments[i].GetQuantity());
        EXPECT_EQ(payments[i].IsPaid(), new_payments[i].IsPaid());
    }
}

TEST_F(PaymentPlanTest, Pay) {
    auto payments = payment_plan.GetPaymentsList();
    EXPECT_FALSE(payments[0].IsPaid());

    payment_plan.Pay();
    payments = payment_plan.GetPaymentsList();
    EXPECT_TRUE(payments[0].IsPaid());

    payment_plan.Pay();
    payments = payment_plan.GetPaymentsList();
    EXPECT_TRUE(payments[1].IsPaid());
}

TEST_F(PaymentPlanTest, ToJson) {
    QJsonObject json = payment_plan.toJson();
    EXPECT_EQ(json["price"].toInt(), price);
    EXPECT_EQ(json["num_of_installments"].toInt(), 12);

    QJsonArray payments_json = json["payments"].toArray();
    auto payments = payment_plan.GetPaymentsList();
    EXPECT_EQ(payments_json.size(), payments.size());

    for (int i = 0; i < payments_json.size(); ++i) {
        QJsonObject payment_json = payments_json[i].toObject();
        EXPECT_FLOAT_EQ(payment_json["quantity"].toDouble(), payments[11-i].GetQuantity());
        EXPECT_EQ(QDate::fromString(payment_json["due_date"].toString(), Qt::ISODate), payments[i].GetDueDate());
        EXPECT_EQ(payment_json["paid"].toBool(), payments[i].IsPaid());
    }
}