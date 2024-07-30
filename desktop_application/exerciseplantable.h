#ifndef EXERCISEPLANTABLE_H
#define EXERCISEPLANTABLE_H

#include <QTableWidget>
#include "inc/member/exercise/exercise.h"

#define EXERCISE_TYPE_TABLE_HEADER 0
#define SET_QUANTITY_TABLE_HEADER 1
#define REPEAT_QUANTITY_TABLE_HEADER 2
#define DURITION_TABLE_HEADER 3

class ExercisePlanTable : public QTableWidget
{
public:
    ExercisePlanTable(std::vector<Exercise*> daily_exercises,
                      QWidget *parent = nullptr);

private:
    QStringList horizontal_headers = {"Type",
                                      "Name",
                                      "Sets",
                                      "Repeats",
                                      "Durition"};
};

#endif // EXERCISEPLANTABLE_H
