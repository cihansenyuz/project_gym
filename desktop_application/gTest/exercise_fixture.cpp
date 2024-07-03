#include "gtest/gtest.h"
#include "../inc/member/exercise/exercise.h"
#include "../inc/member/exercise/cardioworkout.h"
#include "../inc/member/exercise/strengthworkout.h"

#include <QJsonObject>

class ExerciseTestFixture : public ::testing::Test {
protected:
    void SetUp() override {
        // Setup can be used to initialize any resources before each test.
    }

    void TearDown() override {
        // TearDown can be used to release any resources after each test.
    }
};

// Dummy derived class to test the abstract Exercise class
class TestExercise : public Exercise {
public:
    TestExercise(ExerciseType type, ExerciseName name)
        : Exercise(type, name) {}

    QJsonObject toJson() const override {
        QJsonObject json;
        json["type"] = Exercise::toString(GetType());
        json["name"] = Exercise::toString(GetName());
        return json;
    }
};

TEST_F(ExerciseTestFixture, ToStringExerciseType) {
    EXPECT_EQ(Exercise::toString(Cardio), "Cardio");
    EXPECT_EQ(Exercise::toString(Shoulder), "Shoulder");
    EXPECT_EQ(Exercise::toString(Chest), "Chest");
    EXPECT_EQ(Exercise::toString(Back), "Back");
    EXPECT_EQ(Exercise::toString(Arm), "Arm");
    EXPECT_EQ(Exercise::toString(Belly), "Belly");
    EXPECT_EQ(Exercise::toString(Hip), "Hip");
    EXPECT_EQ(Exercise::toString(Leg), "Leg");
}

TEST_F(ExerciseTestFixture, ToStringExerciseName) {
    EXPECT_EQ(Exercise::toString(TreadmillRunning), "Treadmill Running");
    EXPECT_EQ(Exercise::toString(TreadmillWalking), "Treadmill Walking");
    EXPECT_EQ(Exercise::toString(StationaryBike), "Stationary Bike");
    EXPECT_EQ(Exercise::toString(StairClimber), "Stair Climber");
    EXPECT_EQ(Exercise::toString(BenchPress), "Bench Press");
    EXPECT_EQ(Exercise::toString(DumbbellInclinePress), "Dumbbell Incline Press");
    EXPECT_EQ(Exercise::toString(LatPulldown), "Lat Pulldown");
    EXPECT_EQ(Exercise::toString(BarbellRow), "Barbell Row");
    EXPECT_EQ(Exercise::toString(OverheadPress), "Overhead Press");
    EXPECT_EQ(Exercise::toString(DumbbellLateralRaise), "Dumbbell Lateral Raise");
}

TEST_F(ExerciseTestFixture, FromStringToExerciseType) {
    EXPECT_EQ(Exercise::fromStringToExerciseType("Cardio"), Cardio);
    EXPECT_EQ(Exercise::fromStringToExerciseType("Shoulder"), Shoulder);
    EXPECT_EQ(Exercise::fromStringToExerciseType("Chest"), Chest);
    EXPECT_EQ(Exercise::fromStringToExerciseType("Back"), Back);
    EXPECT_EQ(Exercise::fromStringToExerciseType("Arm"), Arm);
    EXPECT_EQ(Exercise::fromStringToExerciseType("Belly"), Belly);
    EXPECT_EQ(Exercise::fromStringToExerciseType("Hip"), Hip);
    EXPECT_EQ(Exercise::fromStringToExerciseType("Leg"), Leg);
}

TEST_F(ExerciseTestFixture, FromStringToExerciseName) {
    EXPECT_EQ(Exercise::fromStringToExerciseName("Treadmill Running"), TreadmillRunning);
    EXPECT_EQ(Exercise::fromStringToExerciseName("Treadmill Walking"), TreadmillWalking);
    EXPECT_EQ(Exercise::fromStringToExerciseName("Stationary Bike"), StationaryBike);
    EXPECT_EQ(Exercise::fromStringToExerciseName("Stair Climber"), StairClimber);
    EXPECT_EQ(Exercise::fromStringToExerciseName("Bench Press"), BenchPress);
    EXPECT_EQ(Exercise::fromStringToExerciseName("Dumbbell Incline Press"), DumbbellInclinePress);
    EXPECT_EQ(Exercise::fromStringToExerciseName("Lat Pulldown"), LatPulldown);
    EXPECT_EQ(Exercise::fromStringToExerciseName("Barbell Row"), BarbellRow);
    EXPECT_EQ(Exercise::fromStringToExerciseName("Overhead Press"), OverheadPress);
    EXPECT_EQ(Exercise::fromStringToExerciseName("Dumbbell Lateral Raise"), DumbbellLateralRaise);
}

TEST_F(ExerciseTestFixture, GetTypeAndName) {
    TestExercise exercise(Cardio, TreadmillRunning);
    EXPECT_EQ(exercise.GetType(), Cardio);
    EXPECT_EQ(exercise.GetName(), TreadmillRunning);
}

TEST_F(ExerciseTestFixture, ToJson) {
    TestExercise exercise(Cardio, TreadmillRunning);
    QJsonObject json = exercise.toJson();
    EXPECT_EQ(json["type"].toString(), "Cardio");
    EXPECT_EQ(json["name"].toString(), "Treadmill Running");
}

class CardioWorkoutTestFixture : public ::testing::Test {
protected:
    void SetUp() override {
        // Setup can be used to initialize any resources before each test.
    }

    void TearDown() override {
        // TearDown can be used to release any resources after each test.
    }
};

TEST_F(CardioWorkoutTestFixture, ConstructorAndGetters) {
    CardioWorkout workout(Cardio, TreadmillRunning, 30); // Example duration of 30 seconds

    EXPECT_EQ(workout.GetType(), Cardio);
    EXPECT_EQ(workout.GetName(), TreadmillRunning);
    EXPECT_EQ(workout.GetDurition(), 30);
}

TEST_F(CardioWorkoutTestFixture, ToJson) {
    CardioWorkout workout(Cardio, TreadmillRunning, 45); // Example duration of 45 seconds

    QJsonObject json = workout.toJson();
    EXPECT_EQ(json["type"].toString(), "Cardio");
    EXPECT_EQ(json["name"].toString(), "Treadmill Running");
    EXPECT_EQ(json["durition"].toInt(), 45);
}

class StrengthWorkoutTestFixture : public ::testing::Test {
protected:
    void SetUp() override {
        // Setup can be used to initialize any resources before each test.
    }

    void TearDown() override {
        // TearDown can be used to release any resources after each test.
    }
};

TEST_F(StrengthWorkoutTestFixture, ConstructorAndGetters) {
    StrengthWorkout workout(Chest, BenchPress, 3, 12); // Example: 3 sets of 12 reps

    EXPECT_EQ(workout.GetType(), Chest);
    EXPECT_EQ(workout.GetName(), BenchPress);
    EXPECT_EQ(workout.GetSet(), 3);
    EXPECT_EQ(workout.GetRepeat(), 12);
}

TEST_F(StrengthWorkoutTestFixture, ToJson) {
    StrengthWorkout workout(Back, BarbellRow, 4, 10); // Example: 4 sets of 10 reps

    QJsonObject json = workout.toJson();
    EXPECT_EQ(json["type"].toString(), "Back");
    EXPECT_EQ(json["name"].toString(), "Barbell Row");
    EXPECT_EQ(json["set"].toInt(), 4);
    EXPECT_EQ(json["repeat"].toInt(), 10);
}