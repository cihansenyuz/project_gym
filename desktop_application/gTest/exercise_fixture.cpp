#include "gtest/gtest.h"
#include "../inc/exercise.h"

class ExerciseTest : public ::testing::Test {
protected:
    void SetUp() override {
        exercise = Exercise::Exercise(Exercise::chest, Exercise::benchPress, 3, 10, 2);
        exercise2 = Exercise::Exercise(Exercise::chest, Exercise::benchPress, 3, 10, 2, QDate::currentDate().addDays(-4));
    }

    Exercise::Exercise exercise;
    Exercise::Exercise exercise2;
};

TEST_F(ExerciseTest, GetType) {
    EXPECT_EQ(exercise.GetType(), Exercise::chest);
}

TEST_F(ExerciseTest, GetName) {
    EXPECT_EQ(exercise.GetName(), Exercise::benchPress);
}

TEST_F(ExerciseTest, GetSet) {
    EXPECT_EQ(exercise.GetSet(), 3);
}

TEST_F(ExerciseTest, GetRepeat) {
    EXPECT_EQ(exercise.GetRepeat(), 10);
}

TEST_F(ExerciseTest, GetCoolDownPeriod) {
    EXPECT_EQ(exercise.GetCoolDownPeriod(), 2);
}

TEST_F(ExerciseTest, GetLastDoneDate) {
    EXPECT_EQ(exercise.GetLastDoneDate(), QDate::currentDate());
}

TEST_F(ExerciseTest, MarkExerciseDone) {
    QDate oldDate = exercise2.GetLastDoneDate();
    exercise2.MarkExerciseDone();
    EXPECT_GT(exercise2.GetLastDoneDate(), oldDate);
    EXPECT_EQ(exercise2.GetLastDoneDate(), QDate::currentDate());
}

TEST_F(ExerciseTest, IsReady) {
    EXPECT_FALSE(exercise.IsReady());
    QDate twoDaysAgo = QDate::currentDate().addDays(-2);
    QDate threeDaysAgo = QDate::currentDate().addDays(-3);
    
    Exercise::Exercise readyExercise(Exercise::chest, Exercise::benchPress, 3, 10, 2, threeDaysAgo);
    EXPECT_TRUE(readyExercise.IsReady());

    Exercise::Exercise notReadyExercise(Exercise::chest, Exercise::benchPress, 3, 10, 2, twoDaysAgo);
    EXPECT_FALSE(notReadyExercise.IsReady());
}

TEST_F(ExerciseTest, ToJson) {
    QJsonObject json = exercise.toJson();
    EXPECT_TRUE(json.contains("type"));
    EXPECT_TRUE(json.contains("name"));
    EXPECT_TRUE(json.contains("set"));
    EXPECT_TRUE(json.contains("repeat"));
    EXPECT_TRUE(json.contains("cooldown_period"));
    EXPECT_TRUE(json.contains("last_done_date"));

    EXPECT_EQ(json["type"].toString(), "chest");
    EXPECT_EQ(json["name"].toString(), "Bench Press");
    EXPECT_EQ(json["set"].toInt(), 3);
    EXPECT_EQ(json["repeat"].toInt(), 10);
    EXPECT_EQ(json["cooldown_period"].toInt(), 2);
    EXPECT_EQ(json["last_done_date"].toString(), QDate::currentDate().toString(Qt::ISODate));
}