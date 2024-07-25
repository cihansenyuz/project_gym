#include <gtest/gtest.h>
#include <QDate>
#include <QJsonObject>
#include <QJsonArray>
#include "../inc/member/payment.h"

class PaymentTest : public ::testing::Test {
protected:
    void SetUp() override {
        start_date = QDate(2023, 1, 1);
        total_payment = 1200;
        installments = 12;
        payment = Payment(total_payment, installments, start_date);
    }

    void TearDown() override {

    }

    QDate start_date;
    int total_payment;
    int installments;
    Payment payment;
};

TEST_F(PaymentTest, Constructor) {
    EXPECT_EQ(payment.GetTotalPayment(), total_payment);
    EXPECT_EQ(payment.GetInstallments(), installments);

    auto payment_plan = payment.GetPaymentPlan();
    EXPECT_EQ(payment_plan.size(), installments);
}

TEST_F(PaymentTest, NextPaymentInfo) {
    auto next_payment = payment.NextPaymentInfo();
    EXPECT_EQ(next_payment.first, start_date);
    EXPECT_FLOAT_EQ(next_payment.second, total_payment / installments);
}

TEST_F(PaymentTest, ToJson) {
    QJsonObject json = payment.toJson();
    EXPECT_EQ(json["total_payment"].toInt(), total_payment);
    EXPECT_EQ(json["installments"].toInt(), installments);

    QJsonArray payment_plan = json["payment_plan"].toArray();
    EXPECT_EQ(payment_plan.size(), installments);

    for (int i = 0; i < payment_plan.size(); ++i) {
        QJsonObject payment_obj = payment_plan[i].toObject();
        EXPECT_EQ(QDate::fromString(payment_obj["date"].toString(), Qt::ISODate), start_date.addMonths(i));
        EXPECT_FLOAT_EQ(payment_obj["amount"].toDouble(), total_payment / installments);
        EXPECT_FALSE(payment_obj["is_paid"].toBool());
    }
}

TEST_F(PaymentTest, SetTotalPayment) {
    int new_total_payment = 2400;
    payment.SetTotalPayment(new_total_payment);
    EXPECT_EQ(payment.GetTotalPayment(), new_total_payment);
}

TEST_F(PaymentTest, SetInstallments) {
    int new_installments = 24;
    payment.SetInstallments(new_installments);
    EXPECT_EQ(payment.GetInstallments(), new_installments);
}

TEST_F(PaymentTest, SetPaymentPlan) {
    std::map<std::pair<QDate, float>, bool> new_payment_plan;
    QDate new_start_date = QDate(2023, 6, 1);
    for (int i = 0; i < 6; ++i) {
        new_payment_plan[std::make_pair(new_start_date.addMonths(i), 200.0f)] = false;
    }
    payment.SetPaymentPlan(new_payment_plan);
    auto payment_plan = payment.GetPaymentPlan();
    EXPECT_EQ(payment_plan.size(), 6);

    auto it = new_payment_plan.begin();
    for (const auto& payment : payment_plan) {
        EXPECT_EQ(payment.first.first, it->first.first);
        EXPECT_FLOAT_EQ(payment.first.second, it->first.second);
        EXPECT_EQ(payment.second, it->second);
        ++it;
    }
}
