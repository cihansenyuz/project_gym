#include <gtest/gtest.h>
#include "../inc/member.h"

#include <QDate>
#include <QJsonObject>

class MemberFixture : public ::testing::Test {
protected:
    void SetUp() override {
        initial_measurement = Measurement(QDate(2023, 1, 1), 70.5, 40.0, 100.0, 30.0, 90.0, 95.0, 60.0);
        member = new Member("John Doe", 30, initial_measurement);
    }

    void TearDown() override {
        delete member;
    }

    void debug(){
        std::cout << "size: " << member->GetAllArchivedSubscriptions().size() << std::endl;
    }

    Member *member;
    Measurement initial_measurement;
};

TEST_F(MemberFixture, TestConstructor) {
    EXPECT_EQ(member->GetName(), "John Doe");
    EXPECT_EQ(member->GetAge(), 30);
    EXPECT_FALSE(member->HasSubscription());
    EXPECT_EQ(member->GetAllMeasurements().size(), 1);
}

TEST_F(MemberFixture, TestSetName) {
    member->SetName("Jane Doe");
    EXPECT_EQ(member->GetName(), "Jane Doe");
}

TEST_F(MemberFixture, TestSetAge) {
    member->SetAge(25);
    EXPECT_EQ(member->GetAge(), 25);
}

TEST_F(MemberFixture, TestSetSubscriptionPeriodWhenEndDateLaterThanCurrent) {
    QDate start_date(2024, 1, 1);
    QDate end_date(2024, 12, 31);
    member->SetSubscriptionPeriod(start_date, end_date);
    EXPECT_TRUE(member->HasSubscription());
    EXPECT_EQ(member->GetSubscriptionStartDate(), start_date);
    EXPECT_EQ(member->GetSubscriptionEndDate(), end_date);
}

TEST_F(MemberFixture, TestSetSubscriptionPeriodWhenEndDateEarlierThanCurrent) {
    QDate start_date(2023, 1, 1);
    QDate end_date(2023, 12, 31);
    member->SetSubscriptionPeriod(start_date, end_date);
    EXPECT_FALSE(member->HasSubscription());
    EXPECT_EQ(member->GetSubscriptionStartDate(), start_date);
    EXPECT_EQ(member->GetSubscriptionEndDate(), end_date);
}

TEST_F(MemberFixture, TestExtendSubscriptionEndDate) {
    QDate start_date(2023, 1, 1);
    QDate end_date(2023, 12, 31);
    member->SetSubscriptionPeriod(start_date, end_date);
    QDate new_end_date(2024, 12, 31);
    member->ExtendSubscriptionEndDate(new_end_date);
    EXPECT_EQ(member->GetSubscriptionEndDate(), new_end_date);
}

TEST_F(MemberFixture, TestToJson) {
    QJsonObject json = member->toJson();
    EXPECT_TRUE(json.contains("name"));
    EXPECT_TRUE(json.contains("age"));
}

TEST_F(MemberFixture, TestGetMeasurementFunctions) {
    EXPECT_FLOAT_EQ(member->GetWeight(1), 70.5);
    EXPECT_FLOAT_EQ(member->GetShoulder(1), 40.0);
    EXPECT_FLOAT_EQ(member->GetChest(1), 100.0);
    EXPECT_FLOAT_EQ(member->GetArm(1), 30.0);
    EXPECT_FLOAT_EQ(member->GetBelly(1), 90.0);
    EXPECT_FLOAT_EQ(member->GetHip(1), 95.0);
    EXPECT_FLOAT_EQ(member->GetLeg(1), 60.0);
    EXPECT_EQ(member->GetTakenDate(1), QDate(2023, 1, 1));
}

TEST_F(MemberFixture, TestAddMeasurement) {
    Measurement new_measurement;
    member->AddMeasurement(new_measurement);
    EXPECT_EQ(member->GetAllMeasurements().size(), 2);
}

TEST_F(MemberFixture, TestGetMeasurementFunctionsWhenAddMeasurementUsed) {
    Measurement new_measurement(QDate(2023, 2, 2), 71.5, 40.6, 101.0, 32.2, 89.3, 95.0, 60.0);
    member->AddMeasurement(new_measurement);

    EXPECT_FLOAT_EQ(member->GetWeight(1), 70.5);
    EXPECT_FLOAT_EQ(member->GetShoulder(1), 40.0);
    EXPECT_FLOAT_EQ(member->GetChest(1), 100.0);
    EXPECT_FLOAT_EQ(member->GetArm(1), 30.0);
    EXPECT_FLOAT_EQ(member->GetBelly(1), 90.0);
    EXPECT_FLOAT_EQ(member->GetHip(1), 95.0);
    EXPECT_FLOAT_EQ(member->GetLeg(1), 60.0);
    EXPECT_EQ(member->GetTakenDate(1), QDate(2023, 1, 1));

    EXPECT_FLOAT_EQ(member->GetWeight(2), 71.5);
    EXPECT_FLOAT_EQ(member->GetShoulder(2), 40.6);
    EXPECT_FLOAT_EQ(member->GetChest(2), 101.0);
    EXPECT_FLOAT_EQ(member->GetArm(2), 32.2);
    EXPECT_FLOAT_EQ(member->GetBelly(2), 89.3);
    EXPECT_FLOAT_EQ(member->GetHip(2), 95.0);
    EXPECT_FLOAT_EQ(member->GetLeg(2), 60.0);
    EXPECT_EQ(member->GetTakenDate(2), QDate(2023, 2, 2));
}

TEST_F(MemberFixture, TestGetName) {
    EXPECT_EQ(member->GetName(), "John Doe");
}

TEST_F(MemberFixture, TestGetAge) {
    EXPECT_EQ(member->GetAge(), 30);
}

TEST_F(MemberFixture, TestHasSubscription) {
    EXPECT_FALSE(member->HasSubscription());
    QDate start_date(2024, 1, 1);
    QDate end_date(2024, 12, 31);
    member->SetSubscriptionPeriod(start_date, end_date);
    EXPECT_TRUE(member->HasSubscription());
}

TEST_F(MemberFixture, TestGetSubscriptionStartDate) {
    QDate start_date(2023, 1, 1);
    QDate end_date(2023, 12, 31);
    member->SetSubscriptionPeriod(start_date, end_date);
    EXPECT_EQ(member->GetSubscriptionStartDate(), start_date);
}

TEST_F(MemberFixture, TestGetSubscriptionEndDate) {
    QDate start_date(2023, 1, 1);
    QDate end_date(2023, 12, 31);
    member->SetSubscriptionPeriod(start_date, end_date);
    EXPECT_EQ(member->GetSubscriptionEndDate(), end_date);
}

TEST_F(MemberFixture, TestEndSubscription){
    QDate start_date(2024, 1, 1);
    QDate end_date(2024, 12, 31);
    member->SetSubscriptionPeriod(start_date, end_date);
    EXPECT_TRUE(member->HasSubscription());
    member->EndSubscription();
    EXPECT_FALSE(member->HasSubscription());
}

TEST_F(MemberFixture, TestAddArchivedSubscription){
    QDate start_date(2024, 1, 1);
    QDate end_date(2024, 12, 31);
    member->SetSubscriptionPeriod(start_date, end_date);
    EXPECT_TRUE(member->HasSubscription());
    EXPECT_EQ(member->GetAllArchivedSubscriptions().size(), 0);
    member->EndSubscription();
    EXPECT_EQ(member->GetAllArchivedSubscriptions().size(), 1);
    EXPECT_EQ(member->GetAllArchivedSubscriptions().back().GetSubscriptionEndDate(), QDate::currentDate());
}

TEST_F(MemberFixture, TestGetAllMeasurements) {
    EXPECT_EQ(member->GetAllMeasurements().size(), 1);
}

TEST_F(MemberFixture, TestGetLastMeasurements) {
    Measurement new_measurement(QDate(2023, 3, 5), 72.5, 41.4, 102.0, 31.2, 88.3, 94.0, 61.0);
    member->AddMeasurement(new_measurement);
    Measurement another_measurement(QDate(2023, 2, 2), 71.5, 40.4, 101.0, 32.2, 89.3, 95.0, 60.0);
    member->AddMeasurement(another_measurement);
    Measurement last_measurement = member->GetLastMeasurements();

    EXPECT_FLOAT_EQ(member->GetWeight(3), last_measurement.GetWeight());
    EXPECT_FLOAT_EQ(member->GetShoulder(3), last_measurement.GetShoulder());
    EXPECT_FLOAT_EQ(member->GetChest(3), last_measurement.GetChest());
    EXPECT_FLOAT_EQ(member->GetArm(3), last_measurement.GetArm());
    EXPECT_FLOAT_EQ(member->GetBelly(3), last_measurement.GetBelly());
    EXPECT_FLOAT_EQ(member->GetHip(3), last_measurement.GetHip());
    EXPECT_FLOAT_EQ(member->GetLeg(3), last_measurement.GetLeg());
    EXPECT_EQ(member->GetTakenDate(3), last_measurement.GetTakenDate());
}
