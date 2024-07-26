#include <gtest/gtest.h>
#include <QDate>
#include <QJsonObject>
#include "../inc/member/payment.h"

class PaymentTest : public ::testing::Test {
protected:
    PaymentTest()
        : quantity(100.0f), due_date(QDate(2023, 1, 1)), payment(quantity, due_date) {}

    void SetUp() override {}

    void TearDown() override {}

    float quantity;
    QDate due_date;
    Payment payment;
};

TEST_F(PaymentTest, Constructor) {
    EXPECT_FLOAT_EQ(payment.GetQuantity(), quantity);
    EXPECT_EQ(payment.GetDueDate(), due_date);
    EXPECT_FALSE(payment.IsPaid());
}

TEST_F(PaymentTest, MakePaid) {
    payment.MakePaid();
    EXPECT_TRUE(payment.IsPaid());
}

TEST_F(PaymentTest, ToJson) {
    QJsonObject json = payment.toJson();
    EXPECT_FLOAT_EQ(json["quantity"].toDouble(), quantity);
    EXPECT_EQ(QDate::fromString(json["due_date"].toString(), Qt::ISODate), due_date);
    EXPECT_FALSE(json["paid"].toBool());

    payment.MakePaid();
    QJsonObject json_paid = payment.toJson();
    EXPECT_TRUE(json_paid["paid"].toBool());
}

TEST_F(PaymentTest, GetQuantity) {
    EXPECT_FLOAT_EQ(payment.GetQuantity(), quantity);
}

TEST_F(PaymentTest, GetDueDate) {
    EXPECT_EQ(payment.GetDueDate(), due_date);
}

TEST_F(PaymentTest, IsPaid) {
    EXPECT_FALSE(payment.IsPaid());
    payment.MakePaid();
    EXPECT_TRUE(payment.IsPaid());
}