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
    EXPECT_TRUE(json["subscription"].toBool());

    QJsonObject archivedJson = subscription->toJson(true);
    EXPECT_EQ(archivedJson["subscription_start_date"].toString(), startDate.toString(Qt::ISODate));
    EXPECT_EQ(archivedJson["subscription_end_date"].toString(), endDate.toString(Qt::ISODate));
    EXPECT_FALSE(archivedJson.contains("subscription"));
}