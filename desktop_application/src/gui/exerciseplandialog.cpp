#include "../../inc/gui/exerciseplandialog.h"
#include "../../ui/ui_exerciseplandialog.h"

ExercisePlanDialog::ExercisePlanDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ExercisePlanDialog)
{
    ui->setupUi(this);
    connect(ui->add_push_button, &QPushButton::clicked,
            this, &ExercisePlanDialog::OnAddButtonClicked);
    connect(ui->remove_push_button, &QPushButton::clicked,
            this, &ExercisePlanDialog::OnRemoveButtonClicked);
    connect(ui->apply_push_button, &QPushButton::clicked,
            this, &ExercisePlanDialog::OnApplyButtonClicked);
    connect(ui->cancel_push_button, &QPushButton::clicked,
            this, &ExercisePlanDialog::OnCancelButtonClicked);

    FillExercisePlanTable();
}

ExercisePlanDialog::~ExercisePlanDialog()
{
    delete ui;
}

void ExercisePlanDialog::FillExercisePlanTable(){
    DeleteExercisePlanTable();

    if(new_weekly_exercise_plan.size() == 0)
        return;

    exercise_day_tabs = std::make_unique<ExerciseWeekView>(new_weekly_exercise_plan);

    ui->exercise_view_layout->addWidget(exercise_day_tabs.get());
    //ui->setLayout(ui->exercise_view_layout);
}

void ExercisePlanDialog::DeleteExercisePlanTable() {
    if(!exercise_day_tabs)
        return;

    while (exercise_day_tabs->count() > 0) {
        QWidget *tab = exercise_day_tabs->widget(0);
        if (tab) {
            QTableWidget *tableWidget = tab->findChild<QTableWidget *>();
            if (tableWidget) {
                tableWidget->clear();
            }
        }
        exercise_day_tabs->removeTab(0);
        delete tab;
    }
}

void ExercisePlanDialog::OnAddButtonClicked(){

}

void ExercisePlanDialog::OnRemoveButtonClicked(){

}

void ExercisePlanDialog::OnAppyButtonClicked(){

}

void ExercisePlanDialog::OnCancelButtonClicked(){

}
