#include "../../../inc/gui/components/exerciseplantabs.h"
#include <QWidget>
#include <QVBoxLayout>

ExercisePlanTabs::ExercisePlanTabs(const std::vector<DailyExercisePlan> &weekly_exercise_plan)
    : QTabWidget() {

    int day_no = 1;
    for(auto &daily_plan : weekly_exercise_plan){
        QWidget *new_tab = new QWidget;
        QVBoxLayout *exercise_day_layout = new QVBoxLayout(new_tab);
        exercise_day_table = new ExerciseDayView(daily_plan.GetDailyExercisePlan(),
                                                                      new_tab);

        exercise_day_layout->addWidget(exercise_day_table);
        new_tab->setLayout(exercise_day_layout);
        addTab(new_tab, QString("Day %1\nCooldown: %2days").arg(day_no++).arg(daily_plan.GetCooldownPeriod()));
    }
}
