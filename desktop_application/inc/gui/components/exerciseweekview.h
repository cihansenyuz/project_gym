#ifndef EXERCISEWEEKVIEW_H
#define EXERCISEWEEKVIEW_H

#include "exercisedayview.h"
#include "../../member/exercise/dailyexerciseplan.h"

class ExerciseWeekView : public QTabWidget
{
public:
    ExerciseWeekView(const std::vector<DailyExercisePlan> &weekly_exercise_plan);

private:
    ExerciseDayView *exercise_day_table;
};

#endif // EXERCISEWEEKVIEW_H
