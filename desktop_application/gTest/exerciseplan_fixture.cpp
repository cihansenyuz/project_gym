#include <gtest/gtest.h>
#include "../inc/exerciseplan.h"

#include <QDate>

/*class ExercisePlanTest : public ::testing::Test {
protected:
    ExercisePlan plan;

    void SetUp() override {}

    void TearDown() override {}
};

TEST_F(ExercisePlanTest, GetExercisePlan) {
    Exercise::Exercise exercise1 = {Exercise::chest, Exercise::benchPress, 3, 10};
    Exercise::Exercise exercise2 = {Exercise::back, Exercise::barbellRow, 3, 10};

    plan.AddNewExercise(exercise1, 2);
    plan.AddNewExercise(exercise2, 3);

    auto planMap = plan.GetExercisePlan();

    // Verify the first exercise
    auto it1 = planMap.find("T+2");
    ASSERT_NE(it1, planMap.end());
    EXPECT_EQ(it1->second.type, Exercise::chest);
    EXPECT_EQ(it1->second.name, Exercise::benchPress);
    EXPECT_EQ(it1->second.set, 3);
    EXPECT_EQ(it1->second.repeat, 10);

    // Verify the second exercise
    auto it2 = planMap.find("T+3");
    ASSERT_NE(it2, planMap.end());
    EXPECT_EQ(it2->second.type, Exercise::back);
    EXPECT_EQ(it2->second.name, Exercise::barbellRow);
    EXPECT_EQ(it2->second.set, 3);
    EXPECT_EQ(it2->second.repeat, 10);
}

TEST_F(ExercisePlanTest, AddNewExercise) {
    Exercise::Exercise exercise = {Exercise::chest, Exercise::benchPress, 3, 10};
    plan.AddNewExercise(exercise, 2);
    
    auto it = plan.GetExercisePlan().find("T+2");
    ASSERT_NE(it, plan.GetExercisePlan().end());
    EXPECT_EQ(it->second.type, Exercise::chest);
    EXPECT_EQ(it->second.name, Exercise::benchPress);
    EXPECT_EQ(it->second.set, 3);
    EXPECT_EQ(it->second.repeat, 10);
}

TEST_F(ExercisePlanTest, SetTargetDateAndRemaningDays) {
    QDate endDate = QDate::currentDate().addDays(10);
    plan.SetTargetDate(endDate);

    short remainingDays = plan.RemaningDays();
    EXPECT_EQ(remainingDays, 10);
}

TEST_F(ExercisePlanTest, RemaningDaysWithPastDate) {
    QDate endDate = QDate::currentDate().addDays(-5);
    plan.SetTargetDate(endDate);

    short remainingDays = plan.RemaningDays();
    EXPECT_EQ(remainingDays, -5);
}*/


class ExercisePlanTest : public ::testing::Test {
protected:
    void SetUp() override {
        Exercise::Exercise exercise1(Exercise::chest, Exercise::benchPress, 3, 10, 2);
        Exercise::Exercise exercise2(Exercise::back, Exercise::latPulldown, 3, 12, 2);

        plan.AddNewExercise(exercise1);
        plan.AddNewExercise(exercise2);

        plan.SetTargetDate(QDate::currentDate().addDays(7), QDate::currentDate());
    }

    ExercisePlan plan;
};

TEST_F(ExercisePlanTest, AddNewExercise) {
    Exercise::Exercise exercise3(Exercise::shoulder, Exercise::overheadPress, 3, 8, 2);
    plan.AddNewExercise(exercise3);

    auto weeklyPlan = plan.GetWeeklyPlan();
    ASSERT_EQ(weeklyPlan.size(), 3);
    EXPECT_EQ(weeklyPlan[2].GetName(), Exercise::overheadPress);
    EXPECT_EQ(weeklyPlan[2].GetType(), Exercise::shoulder);
}

TEST_F(ExercisePlanTest, GetWeeklyPlan) {
    auto weeklyPlan = plan.GetWeeklyPlan();
    ASSERT_EQ(weeklyPlan.size(), 2);
    EXPECT_EQ(weeklyPlan[0].GetName(), Exercise::benchPress);
    EXPECT_EQ(weeklyPlan[1].GetName(), Exercise::latPulldown);
}

TEST_F(ExercisePlanTest, SetTargetDate) {
    QDate newEndDate = QDate::currentDate().addDays(10);
    plan.SetTargetDate(newEndDate);
    auto period = plan.GetExercisePeriod();
    EXPECT_EQ(period.second, newEndDate);
}

TEST_F(ExercisePlanTest, RemaningDays) {
    EXPECT_EQ(plan.RemaningDays(), 7);
}

TEST_F(ExercisePlanTest, ClearExercisePlan) {
    plan.ClearExercisePlan();
    auto weeklyPlan = plan.GetWeeklyPlan();
    EXPECT_TRUE(weeklyPlan.empty());
    EXPECT_EQ(plan.RemaningDays(), 0);
}

TEST_F(ExercisePlanTest, ToJson) {
    QJsonObject json = plan.toJson();
    EXPECT_TRUE(json.contains("start_day"));
    EXPECT_TRUE(json.contains("end_day"));
    EXPECT_TRUE(json.contains("weekly_plan"));

    QJsonArray weeklyPlanArray = json["weekly_plan"].toArray();
    EXPECT_EQ(weeklyPlanArray.size(), 2);

    QJsonObject exerciseJson1 = weeklyPlanArray[0].toObject();
    EXPECT_EQ(exerciseJson1["name"].toString(), "Bench Press");
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}