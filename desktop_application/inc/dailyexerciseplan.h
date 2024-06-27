#ifndef DAILYEXERCISEPLAN_H
#define DAILYEXERCISEPLAN_H

#include <vector>
#include <QJsonObject>
#include "exercise.h"

class DailyExercisePlan
{
public:
    DailyExercisePlan() = default;
    void AddNewExercise(const Exercise &new_exercise);
    QJsonObject toJson() const;

    void GetCooldownPeriod() const;

private:
    std::vector<Exercise> daily_plan_;
    short cooldown_period_;
};

#endif // DAILYEXERCISEPLAN_H
