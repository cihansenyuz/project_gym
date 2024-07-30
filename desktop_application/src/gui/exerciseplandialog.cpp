#include "../../inc/gui/exerciseplandialog.h"
#include "../../ui/ui_exerciseplandialog.h"
#include "../../inc/member/exercise/cardioworkout.h"
#include "../../inc/member/exercise/strengthworkout.h"

ExercisePlanDialog::ExercisePlanDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ExercisePlanDialog)
{
    ui->setupUi(this);
    connect(ui->add_push_button, &QPushButton::clicked,
            this, &ExercisePlanDialog::OnAddButtonClicked);
    connect(ui->remove_push_button, &QPushButton::clicked,
            this, &ExercisePlanDialog::OnRemoveButtonClicked);
    connect(ui->save_daily_push_button, &QPushButton::clicked,
            this, &ExercisePlanDialog::OnSaveDailyButtonClicked);
    connect(ui->add_daily_push_button, &QPushButton::clicked,
            this, &ExercisePlanDialog::OnAddDailyButtonClicked);
    connect(ui->apply_push_button, &QPushButton::clicked,
            this, &ExercisePlanDialog::OnApplyButtonClicked);
    connect(ui->cancel_push_button, &QPushButton::clicked,
            this, &ExercisePlanDialog::OnCancelButtonClicked);

    ui->type_combo_box->addItem("Cardio");
    ui->type_combo_box->addItem("Shoulder");
    ui->type_combo_box->addItem("Chest");
    ui->type_combo_box->addItem("Back");
    ui->type_combo_box->addItem("Arm");
    ui->type_combo_box->addItem("Belly");
    ui->type_combo_box->addItem("Hip");
    ui->type_combo_box->addItem("Leg");

    ui->name_combo_box->addItem("Treadmill Running");
    ui->name_combo_box->addItem("Treadmill Walking");
    ui->name_combo_box->addItem("Stationary Bike");
    ui->name_combo_box->addItem("Stair Climber");
    ui->name_combo_box->addItem("Bench Press");
    ui->name_combo_box->addItem("Dumbbell Incline Press");
    ui->name_combo_box->addItem("Lat Pulldown");
    ui->name_combo_box->addItem("Barbell Row");
    ui->name_combo_box->addItem("Overhead Press");
    ui->name_combo_box->addItem("Dumbbell Lateral Raise");

    new_weekly_exercise_plan.push_back(new_daily_plan);
    ui->start_date_edit->setDate(QDate::currentDate());
    ui->end_date_edit->setDate(QDate::currentDate());
    ui->add_daily_push_button->setEnabled(false);
    ui->apply_push_button->setEnabled(false);
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
    exercise_day_tabs->setCurrentIndex(current_day);
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
    Exercise *exercise;
    ExerciseType type = Exercise::fromStringToExerciseType(ui->type_combo_box->currentText());
    if(type == Cardio){
        CardioWorkout *cardio_exercise = new CardioWorkout(type,
                                                    Exercise::fromStringToExerciseName(ui->name_combo_box->currentText()),
                                                    ui->durition_spin_box->value());
        exercise = static_cast<CardioWorkout*>(cardio_exercise);
    }
    else{
        StrengthWorkout *strength_exercise = new StrengthWorkout(type,
                                                         Exercise::fromStringToExerciseName(ui->name_combo_box->currentText()),
                                                         ui->set_spin_box->value(),
                                                         ui->repeat_spin_box->value());
        exercise = static_cast<StrengthWorkout*>(strength_exercise);
    }

    new_daily_plan.AddNewExercise(exercise);
    new_weekly_exercise_plan.at(current_day) = new_daily_plan;
    FillExercisePlanTable();
}

void ExercisePlanDialog::OnRemoveButtonClicked(){

}

void ExercisePlanDialog::OnSaveDailyButtonClicked(){
    new_daily_plan.SetCooldownPeriod(ui->cooldown_spin_box->value());
    new_weekly_exercise_plan.at(current_day) = new_daily_plan;
    new_daily_plan.Clear();
    FillExercisePlanTable();
    ui->add_daily_push_button->setEnabled(true);
    ui->apply_push_button->setEnabled(true);
    ui->save_daily_push_button->setEnabled(false);
}

void ExercisePlanDialog::OnAddDailyButtonClicked(){
    current_day++;
    new_daily_plan.Clear();
    new_weekly_exercise_plan.push_back(new_daily_plan);
    FillExercisePlanTable();
    ui->add_daily_push_button->setEnabled(false);
    ui->apply_push_button->setEnabled(false);
    ui->save_daily_push_button->setEnabled(true);
}

void ExercisePlanDialog::OnApplyButtonClicked(){
    emit NewWeeklyPlanReady(new_weekly_exercise_plan,
                            ui->start_date_edit->date(),
                            ui->end_date_edit->date());
    close();
}

void ExercisePlanDialog::OnCancelButtonClicked(){
    close();
}
