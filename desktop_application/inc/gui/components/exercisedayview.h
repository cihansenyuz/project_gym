#ifndef EXERCISEDAYVIEW_H
#define EXERCISEDAYVIEW_H

#include <QTableWidget>
#include "../../member/exercise/exercise.h"

#define EXERCISE_TYPE_TABLE_HEADER 0
#define SET_QUANTITY_TABLE_HEADER 1
#define REPEAT_QUANTITY_TABLE_HEADER 2
#define DURITION_TABLE_HEADER 3

class ExerciseDayView : public QTableWidget
{
public:
    ExerciseDayView(std::vector<Exercise*> daily_exercises,
                      QWidget *parent = nullptr);

private:
    QStringList horizontal_headers = {"Type",
                                      "Sets",
                                      "Repeats",
                                      "Durition"};
};

#endif // EXERCISEDAYVIEW_H
