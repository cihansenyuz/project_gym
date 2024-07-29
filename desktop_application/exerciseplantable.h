#ifndef EXERCISEPLANTABLE_H
#define EXERCISEPLANTABLE_H

#include <QTableWidget>
#include "inc/member/exercise/exercise.h"

class ExercisePlanTable : public QTableWidget
{
public:
    ExercisePlanTable(std::vector<Exercise*> daily_exercises,
                      int rows, int columns,
                      QWidget *parent = nullptr);
};

#endif // EXERCISEPLANTABLE_H
