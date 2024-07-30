#include "exerciseplantable.h"
#include "inc/member/exercise/cardioworkout.h"
#include "inc/member/exercise/strengthworkout.h"

ExercisePlanTable::ExercisePlanTable(std::vector<Exercise*> daily_exercises, QWidget *parent)
    : QTableWidget(daily_exercises.size(), 4, parent) {

    setHorizontalHeaderLabels(horizontal_headers);

    for(int i=0; i < daily_exercises.size(); i++){
        QTableWidgetItem *header_item = new QTableWidgetItem(Exercise::toString(daily_exercises[i]->GetName()));
        setVerticalHeaderItem(i, header_item);

        ExerciseType type = daily_exercises[i]->GetType();
        QTableWidgetItem *item_type = new QTableWidgetItem(Exercise::toString(type));
        setItem(i, EXERCISE_TYPE_TABLE_HEADER, item_type);

        if(type == Cardio){
            CardioWorkout* casted_exercise = dynamic_cast<CardioWorkout*>(daily_exercises[i]);
            QTableWidgetItem *item_durition = new QTableWidgetItem(QString::number(casted_exercise->GetDurition()));
            item_durition->setTextAlignment(Qt::AlignCenter);
            setItem(i, DURITION_TABLE_HEADER, item_durition);
        }
        else{
            StrengthWorkout* casted_exercise = dynamic_cast<StrengthWorkout*>(daily_exercises[i]);
            QTableWidgetItem *item_set = new QTableWidgetItem(QString::number(casted_exercise->GetSet()));
            item_set->setTextAlignment(Qt::AlignCenter);
            setItem(i, SET_QUANTITY_TABLE_HEADER, item_set);
            QTableWidgetItem *item_repeat = new QTableWidgetItem(QString::number(casted_exercise->GetRepeat()));
            item_repeat->setTextAlignment(Qt::AlignCenter);
            setItem(i, REPEAT_QUANTITY_TABLE_HEADER, item_repeat);
        }
        for (int col = 0; col < columnCount(); ++col) {
            resizeColumnToContents(col);
        }
    }
}
