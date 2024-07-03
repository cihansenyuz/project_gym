#include <gtest/gtest.h>
#include "../inc/member/measurement.h"
#include <QDate>
#include <QJsonObject>

class MeasurementFixture : public testing::Test {
protected:
    Measurement measurement_stack;
    Measurement measurement_stack2{QDate(2023, 1, 1), 70.5, 40.0, 100.0, 30.0, 90.0, 95.0, 60.0};
    Measurement *measurement_heap;

    void SetUp() override {
        measurement_stack = Measurement(QDate(2023, 1, 1), 70.5, 40.0, 100.0, 30.0, 90.0, 95.0, 60.0);
        measurement_heap = new Measurement(QDate(2023, 1, 1), 70.5, 40.0, 100.0, 30.0, 90.0, 95.0, 60.0);
    }
    void TearDown() override {
        delete measurement_heap;
    }
};

TEST_F(MeasurementFixture, TestGetWeight) {
    EXPECT_FLOAT_EQ(measurement_stack.GetWeight(), 70.5);
    EXPECT_FLOAT_EQ(measurement_stack2.GetWeight(), 70.5);
    EXPECT_FLOAT_EQ(measurement_heap->GetWeight(), 70.5);
}

TEST_F(MeasurementFixture, TestGetShoulder) {
    EXPECT_FLOAT_EQ(measurement_stack.GetShoulder(), 40.0);
    EXPECT_FLOAT_EQ(measurement_stack2.GetShoulder(), 40.0);
    EXPECT_FLOAT_EQ(measurement_heap->GetShoulder(), 40.0);
}

TEST_F(MeasurementFixture, TestGetChest) {
    EXPECT_FLOAT_EQ(measurement_stack.GetChest(), 100.0);
    EXPECT_FLOAT_EQ(measurement_stack2.GetChest(), 100.0);
    EXPECT_FLOAT_EQ(measurement_heap->GetChest(), 100.0);
}

TEST_F(MeasurementFixture, TestGetArm) {
    EXPECT_FLOAT_EQ(measurement_stack.GetArm(), 30.0);
    EXPECT_FLOAT_EQ(measurement_stack2.GetArm(), 30.0);
    EXPECT_FLOAT_EQ(measurement_heap->GetArm(), 30.0);
}

TEST_F(MeasurementFixture, TestGetBelly) {
    EXPECT_FLOAT_EQ(measurement_stack.GetBelly(), 90.0);
    EXPECT_FLOAT_EQ(measurement_stack2.GetBelly(), 90.0);
    EXPECT_FLOAT_EQ(measurement_heap->GetBelly(), 90.0);
}

TEST_F(MeasurementFixture, TestGetHip) {
    EXPECT_FLOAT_EQ(measurement_stack.GetHip(), 95.0);
    EXPECT_FLOAT_EQ(measurement_stack2.GetHip(), 95.0);
    EXPECT_FLOAT_EQ(measurement_heap->GetHip(), 95.0);
}

TEST_F(MeasurementFixture, TestGetLeg) {
    EXPECT_FLOAT_EQ(measurement_stack.GetLeg(), 60.0);
    EXPECT_FLOAT_EQ(measurement_stack2.GetLeg(), 60.0);
    EXPECT_FLOAT_EQ(measurement_heap->GetLeg(), 60.0);
}

TEST_F(MeasurementFixture, TestGetTakenDate) {
    EXPECT_EQ(measurement_stack.GetTakenDate(), QDate(2023, 1, 1));
    EXPECT_EQ(measurement_stack2.GetTakenDate(), QDate(2023, 1, 1));
    EXPECT_EQ(measurement_heap->GetTakenDate(), QDate(2023, 1, 1));
}

TEST_F(MeasurementFixture, TestToJson) {
    QJsonObject json = measurement_stack.toJson();
    EXPECT_FLOAT_EQ(json["weight"].toDouble(), 70.5);
    EXPECT_FLOAT_EQ(json["shoulder"].toDouble(), 40.0);
    EXPECT_FLOAT_EQ(json["chest"].toDouble(), 100.0);
    EXPECT_FLOAT_EQ(json["arm"].toDouble(), 30.0);
    EXPECT_FLOAT_EQ(json["belly"].toDouble(), 90.0);
    EXPECT_FLOAT_EQ(json["hip"].toDouble(), 95.0);
    EXPECT_FLOAT_EQ(json["leg"].toDouble(), 60.0);
    EXPECT_EQ(json["taken_date"].toString(), QDate(2023, 1, 1).toString(Qt::ISODate));

    QJsonObject json2 = measurement_stack2.toJson();
    EXPECT_FLOAT_EQ(json2["weight"].toDouble(), 70.5);
    EXPECT_FLOAT_EQ(json2["shoulder"].toDouble(), 40.0);
    EXPECT_FLOAT_EQ(json2["chest"].toDouble(), 100.0);
    EXPECT_FLOAT_EQ(json2["arm"].toDouble(), 30.0);
    EXPECT_FLOAT_EQ(json2["belly"].toDouble(), 90.0);
    EXPECT_FLOAT_EQ(json2["hip"].toDouble(), 95.0);
    EXPECT_FLOAT_EQ(json2["leg"].toDouble(), 60.0);
    EXPECT_EQ(json2["taken_date"].toString(), QDate(2023, 1, 1).toString(Qt::ISODate));

    QJsonObject json3 = measurement_heap->toJson();
    EXPECT_FLOAT_EQ(json3["weight"].toDouble(), 70.5);
    EXPECT_FLOAT_EQ(json3["shoulder"].toDouble(), 40.0);
    EXPECT_FLOAT_EQ(json3["chest"].toDouble(), 100.0);
    EXPECT_FLOAT_EQ(json3["arm"].toDouble(), 30.0);
    EXPECT_FLOAT_EQ(json3["belly"].toDouble(), 90.0);
    EXPECT_FLOAT_EQ(json3["hip"].toDouble(), 95.0);
    EXPECT_FLOAT_EQ(json3["leg"].toDouble(), 60.0);
    EXPECT_EQ(json3["taken_date"].toString(), QDate(2023, 1, 1).toString(Qt::ISODate));
}
