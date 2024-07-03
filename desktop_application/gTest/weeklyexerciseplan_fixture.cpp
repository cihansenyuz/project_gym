#include "gtest/gtest.h"
#include "../inc/member/exercise/weeklyexerciseplan.h"
#include "../inc/member/exercise/dailyexerciseplan.h"
#include "../inc/member/exercise/cardioworkout.h"
#include "../inc/member/exercise/strengthworkout.h"

#include <QDate>

class WeeklyExercisePlanTestFixture : public ::testing::Test {
protected:
    void SetUp() override {
        // Initialize resources before each test.
        cardioWorkout1 = new CardioWorkout(Cardio, TreadmillRunning, 30);
        strengthWorkout1 = new StrengthWorkout(Chest, BenchPress, 3, 12);

        dailyPlan1.AddNewExercise(cardioWorkout1);
        dailyPlan2.AddNewExercise(strengthWorkout1);
    }

    void TearDown() override {
        // Clean up resources after each test.
        delete cardioWorkout1;
        delete strengthWorkout1;
    }

    CardioWorkout *cardioWorkout1;
    StrengthWorkout *strengthWorkout1;
    DailyExercisePlan dailyPlan1;
    DailyExercisePlan dailyPlan2;
};

TEST_F(WeeklyExercisePlanTestFixture, ConstructorAndGetters) {
    QDate startDate = QDate::currentDate();
    QDate endDate = startDate.addDays(7);
    WeeklyExercisePlan plan(endDate, startDate);

    auto period = plan.GetWeeklyExercisePlanPeriod();
    EXPECT_EQ(period.first, startDate);
    EXPECT_EQ(period.second, endDate);
}

TEST_F(WeeklyExercisePlanTestFixture, AddAndClearDailyExercisePlan) {
    WeeklyExercisePlan plan;
    plan.AddNewDailyExercisePlan(dailyPlan1);
    plan.AddNewDailyExercisePlan(dailyPlan2);

    auto weeklyPlan = plan.GetWeeklyExercisePlan();
    ASSERT_EQ(weeklyPlan.size(), 2);

    plan.ClearWeeklyExercisePlan();
    weeklyPlan = plan.GetWeeklyExercisePlan();
    EXPECT_TRUE(weeklyPlan.empty());
}

TEST_F(WeeklyExercisePlanTestFixture, SetAndGetWeeklyExercisePlan) {
    WeeklyExercisePlan plan;
    std::vector<DailyExercisePlan> newWeeklyPlan = {dailyPlan1, dailyPlan2};
    plan.SetWeeklyExercisePlan(newWeeklyPlan);

    auto weeklyPlan = plan.GetWeeklyExercisePlan();
    ASSERT_EQ(weeklyPlan.size(), 2);
    EXPECT_EQ(weeklyPlan[0].toJson(), dailyPlan1.toJson());
    EXPECT_EQ(weeklyPlan[1].toJson(), dailyPlan2.toJson());
}

TEST_F(WeeklyExercisePlanTestFixture, SetAndCheckWeeklyExercisePlanPeriod) {
    WeeklyExercisePlan plan;
    QDate startDate = QDate::currentDate();
    QDate endDate = startDate.addDays(7);
    plan.SetWeeklyExercisePlanPeriod(startDate, endDate);

    auto period = plan.GetWeeklyExercisePlanPeriod();
    EXPECT_EQ(period.first, startDate);
    EXPECT_EQ(period.second, endDate);
}

TEST_F(WeeklyExercisePlanTestFixture, GetRemainingDays) {
    QDate startDate = QDate::currentDate();
    QDate endDate = startDate.addDays(7);
    WeeklyExercisePlan plan(endDate, startDate);

    EXPECT_EQ(plan.GetRemainingDays(), 7);
}

TEST_F(WeeklyExercisePlanTestFixture, HasWeeklyExercisePlan) {
    WeeklyExercisePlan plan;
    EXPECT_FALSE(plan.HasWeeklyExercisePlan());

    plan.AddNewDailyExercisePlan(dailyPlan1);
    EXPECT_TRUE(plan.HasWeeklyExercisePlan());
}

TEST_F(WeeklyExercisePlanTestFixture, EndWeeklyExercisePlan) {
    QDate startDate = QDate::currentDate().addDays(-3);
    QDate endDate = QDate::currentDate().addDays(4);
    WeeklyExercisePlan plan(endDate, startDate);

    plan.EndWeeklyExercisePlan();
    auto period = plan.GetWeeklyExercisePlanPeriod();
    EXPECT_EQ(period.second, QDate::currentDate());
}

TEST_F(WeeklyExercisePlanTestFixture, ToJson) {
    QDate startDate = QDate::currentDate();
    QDate endDate = startDate.addDays(7);
    WeeklyExercisePlan plan(endDate, startDate);

    plan.AddNewDailyExercisePlan(dailyPlan1);
    plan.AddNewDailyExercisePlan(dailyPlan2);

    QJsonObject json = plan.toJson();
    QJsonArray weeklyPlanJson = json["weekly_exercise_plan"].toArray();
    ASSERT_EQ(weeklyPlanJson.size(), 2);

    QJsonObject dailyPlan1Json = weeklyPlanJson[0].toObject();
    QJsonObject dailyPlan2Json = weeklyPlanJson[1].toObject();

    EXPECT_EQ(dailyPlan1Json["daily_exercise"].toArray().size(), 1);
    EXPECT_EQ(dailyPlan2Json["daily_exercise"].toArray().size(), 1);

    EXPECT_EQ(json["start_date"].toString(), startDate.toString(Qt::ISODate));
    EXPECT_EQ(json["end_date"].toString(), endDate.toString(Qt::ISODate));
}