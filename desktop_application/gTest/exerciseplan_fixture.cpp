#include <gtest/gtest.h>
#include "../inc/exerciseplan.h"

#include <QDate>

class ExercisePlanTest : public ::testing::Test {
protected:
    ExercisePlan plan;

    void SetUp() override {}

    void TearDown() override {}
};

TEST_F(ExercisePlanTest, GetExercisePlan) {
    Exercise::Exercise_t exercise1 = {Exercise::chest, Exercise::benchPress, 3, 10};
    Exercise::Exercise_t exercise2 = {Exercise::back, Exercise::barbellRow, 3, 10};

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
    Exercise::Exercise_t exercise = {Exercise::chest, Exercise::benchPress, 3, 10};
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
}
