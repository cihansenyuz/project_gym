#ifndef EXERCISEPLANTABS_H
#define EXERCISEPLANTABS_H

#include "exerciseplantable.h"
#include "../../member/exercise/dailyexerciseplan.h"

class ExercisePlanTabs : public QTabWidget
{
public:
    ExercisePlanTabs(const std::vector<DailyExercisePlan> &weekly_exercise_plan);

private:
    ExercisePlanTable *exercise_day_table;
};

#endif // EXERCISEPLANTABS_H
