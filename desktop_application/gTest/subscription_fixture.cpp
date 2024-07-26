#include <gtest/gtest.h>
#include "../inc/member/subscription.h"

#include <QDate>

class SubscriptionTestFixture : public ::testing::Test {
protected:
    void SetUp() override {
        // Setup can be used to initialize any resources before each test.
        startDate = QDate::currentDate();
        endDate = startDate.addDays(30);
        subscription = new Subscription(startDate, endDate, true);
    }

    void TearDown() override {
        // Clean up resources after each test.
        delete subscription;
    }

    QDate startDate;
    QDate endDate;
    Subscription *subscription;
};

TEST_F(SubscriptionTestFixture, ConstructorAndGetters) {
    EXPECT_EQ(subscription->GetSubscriptionStartDate(), startDate);
    EXPECT_EQ(subscription->GetSubscriptionEndDate(), endDate);
    EXPECT_TRUE(subscription->HasSubscription());
}

TEST_F(SubscriptionTestFixture, SetSubscriptionPeriod) {
    QDate newStartDate = QDate::currentDate().addDays(-10);
    QDate newEndDate = QDate::currentDate().addDays(20);
    subscription->SetSubscriptionPeriod(newStartDate, newEndDate);

    EXPECT_EQ(subscription->GetSubscriptionStartDate(), newStartDate);
    EXPECT_EQ(subscription->GetSubscriptionEndDate(), newEndDate);
    EXPECT_TRUE(subscription->HasSubscription());
}

TEST_F(SubscriptionTestFixture, ExtendSubscriptionEndDate) {
    QDate newEndDate = endDate.addDays(15);
    subscription->ExtendSubscriptionEndDate(newEndDate);

    EXPECT_EQ(subscription->GetSubscriptionEndDate(), newEndDate);
}

TEST_F(SubscriptionTestFixture, EndSubscription) {
    subscription->EndSubscription(false);
    EXPECT_FALSE(subscription->HasSubscription());
    EXPECT_EQ(subscription->GetSubscriptionEndDate(), endDate);

    subscription->EndSubscription(true);
    EXPECT_FALSE(subscription->HasSubscription());
    EXPECT_EQ(subscription->GetSubscriptionEndDate(), QDate::currentDate());
}

TEST_F(SubscriptionTestFixture, ToJson) {
    QJsonObject json = subscription->toJson();
    EXPECT_EQ(json["subscription_start_date"].toString(), startDate.toString(Qt::ISODate));
    EXPECT_EQ(json["subscription_end_date"].toString(), endDate.toString(Qt::ISODate));
    EXPECT_TRUE(json["status"].toBool());

    QJsonObject archivedJson = subscription->toJson(true);
    EXPECT_EQ(archivedJson["subscription_start_date"].toString(), startDate.toString(Qt::ISODate));
    EXPECT_EQ(archivedJson["subscription_end_date"].toString(), endDate.toString(Qt::ISODate));
    EXPECT_FALSE(archivedJson.contains("status"));
}

TEST_F(SubscriptionTestFixture, PaymentPlanIntegration) {

    subscription->SetPaymentPlan(PaymentPlan(1200, 12, startDate));

    EXPECT_EQ(subscription->GetPrice(), 1200);
    EXPECT_EQ(subscription->GetNumOfInstallments(), 12);

    auto payments = subscription->GetPaymentsList();
    EXPECT_EQ(payments.size(), 12);

    for (int i = 0; i < 12; ++i) {
        EXPECT_EQ(payments[i].GetDueDate(), startDate.addMonths(11-i));
        EXPECT_FLOAT_EQ(payments[i].GetQuantity(), 1200 / 12);
        EXPECT_FALSE(payments[i].IsPaid());
    }

    subscription->Pay();
    EXPECT_EQ(subscription->RemainingInstallmentQuantity(), 11);
    EXPECT_FLOAT_EQ(subscription->RemainingPaymentsTotal(), 1200 - (1200 / 12));
}