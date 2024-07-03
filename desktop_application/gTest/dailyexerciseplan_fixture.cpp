#include <gtest/gtest.h>
#include "../inc/member/exercise/dailyexerciseplan.h"
#include "../inc/member/exercise/cardioworkout.h"
#include "../inc/member/exercise/strengthworkout.h"

class DailyExercisePlanTestFixture : public ::testing::Test {
protected:
    void SetUp() override {
        // Setup can be used to initialize any resources before each test.
        cardioWorkout1 = new CardioWorkout(Cardio, TreadmillRunning, 30);
        cardioWorkout2 = new CardioWorkout(Cardio, StationaryBike, 45);
        strengthWorkout1 = new StrengthWorkout(Chest, BenchPress, 3, 12);
        strengthWorkout2 = new StrengthWorkout(Back, BarbellRow, 4, 10);
    }

    void TearDown() override {
        // Clean up resources after each test.
        delete cardioWorkout1;
        delete cardioWorkout2;
        delete strengthWorkout1;
        delete strengthWorkout2;
    }

    CardioWorkout *cardioWorkout1;
    CardioWorkout *cardioWorkout2;
    StrengthWorkout *strengthWorkout1;
    StrengthWorkout *strengthWorkout2;
};

TEST_F(DailyExercisePlanTestFixture, AddNewExercise) {
    DailyExercisePlan plan;
    plan.AddNewExercise(cardioWorkout1);
    plan.AddNewExercise(strengthWorkout1);

    auto dailyPlan = plan.GetDailyExercisePlan();
    ASSERT_EQ(dailyPlan.size(), 2);
    EXPECT_EQ(dailyPlan[0], cardioWorkout1);
    EXPECT_EQ(dailyPlan[1], strengthWorkout1);
}

TEST_F(DailyExercisePlanTestFixture, SetAndGetCooldownPeriod) {
    DailyExercisePlan plan;
    plan.SetCooldownPeriod(3);

    EXPECT_EQ(plan.GetCooldownPeriod(), 3);
}

TEST_F(DailyExercisePlanTestFixture, SetAndGetDailyExercisePlan) {
    DailyExercisePlan plan;
    std::vector<Exercise*> newPlan = {cardioWorkout1, cardioWorkout2, strengthWorkout1};
    plan.SetDailyExecisePlan(newPlan);

    auto dailyPlan = plan.GetDailyExercisePlan();
    ASSERT_EQ(dailyPlan.size(), 3);
    EXPECT_EQ(dailyPlan[0], cardioWorkout1);
    EXPECT_EQ(dailyPlan[1], cardioWorkout2);
    EXPECT_EQ(dailyPlan[2], strengthWorkout1);
}

TEST_F(DailyExercisePlanTestFixture, ToJson) {
    DailyExercisePlan plan;
    plan.AddNewExercise(cardioWorkout1);
    plan.AddNewExercise(strengthWorkout1);
    plan.SetCooldownPeriod(2);

    QJsonObject json = plan.toJson();
    QJsonArray dailyPlanJson = json["daily_exercise"].toArray();
    ASSERT_EQ(dailyPlanJson.size(), 2);

    QJsonObject exercise1Json = dailyPlanJson[0].toObject();
    EXPECT_EQ(exercise1Json["type"].toString(), "Cardio");
    EXPECT_EQ(exercise1Json["name"].toString(), "Treadmill Running");
    EXPECT_EQ(exercise1Json["durition"].toInt(), 30);

    QJsonObject exercise2Json = dailyPlanJson[1].toObject();
    EXPECT_EQ(exercise2Json["type"].toString(), "Chest");
    EXPECT_EQ(exercise2Json["name"].toString(), "Bench Press");
    EXPECT_EQ(exercise2Json["set"].toInt(), 3);
    EXPECT_EQ(exercise2Json["repeat"].toInt(), 12);

    EXPECT_EQ(json["cooldown_period"].toInt(), 2);
}