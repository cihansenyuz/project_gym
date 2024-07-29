#include "exerciseplantable.h"
#include "inc/member/exercise/cardioworkout.h"
#include "inc/member/exercise/strengthworkout.h"

ExercisePlanTable::ExercisePlanTable(std::vector<Exercise*> daily_exercises, int rows, int columns, QWidget *parent)
    : QTableWidget(rows, columns, parent) {

    setHorizontalHeaderLabels(QStringList{"Type",
                                          "Name",
                                          "Sets",
                                          "Repeats",
                                          "Durition"});

    for(int i=0; i < daily_exercises.size(); i++){
        QTableWidgetItem *header_item = new QTableWidgetItem(Exercise::toString(daily_exercises[i]->GetName()));
        setVerticalHeaderItem(i, header_item);

        ExerciseType type = daily_exercises[i]->GetType();
        QTableWidgetItem *item_type = new QTableWidgetItem(Exercise::toString(type));
        setItem(i, 0, item_type);

        if(type == Cardio){
            CardioWorkout* casted_exercise = dynamic_cast<CardioWorkout*>(daily_exercises[i]);
            QTableWidgetItem *item_durition = new QTableWidgetItem(QString::number(casted_exercise->GetDurition()));
            item_durition->setTextAlignment(Qt::AlignCenter);
            setItem(i, 3, item_durition);
        }
        else{
            StrengthWorkout* casted_exercise = dynamic_cast<StrengthWorkout*>(daily_exercises[i]);
            QTableWidgetItem *item_set = new QTableWidgetItem(QString::number(casted_exercise->GetSet()));
            item_set->setTextAlignment(Qt::AlignCenter);
            setItem(i, 1, item_set);
            QTableWidgetItem *item_repeat = new QTableWidgetItem(QString::number(casted_exercise->GetRepeat()));
            item_repeat->setTextAlignment(Qt::AlignCenter);
            setItem(i, 2, item_repeat);
        }
        for (int col = 0; col < columnCount(); ++col) {
            resizeColumnToContents(col);
        }
    }
}
