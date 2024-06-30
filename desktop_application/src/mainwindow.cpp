#include "../inc/mainwindow.h"
#include "../ui/ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //////// TEST & DEBUG SECTION /////////

    Member* current_member = member_manager.GetMember("cihan");
    /*if(current_member){
        qDebug() << "current selected member: " << current_member->GetName();

        current_member->SetAge(22);
        member_manager.SaveChangesOnMember(*current_member);
    }
    else
        qDebug() << "no member found";*/

    /*DailyExercisePlan daily_plan;
    CardioWorkout *exercise = new CardioWorkout(ExerciseType::Cardio, ExerciseName::TreadmillRunning, 20);
    CardioWorkout *exercise2 = new CardioWorkout(ExerciseType::Cardio, ExerciseName::StairClimber, 10);
    StrengthWorkout *exercise3 = new StrengthWorkout(ExerciseType::Chest, ExerciseName::BenchPress, 3, 8);

    daily_plan.AddNewExercise(exercise);
    daily_plan.AddNewExercise(exercise2);
    daily_plan.AddNewExercise(exercise3);
    daily_plan.SetCooldownPeriod(3);

    member_manager.GetCurrentMember()->AddNewDailyExercisePlan(daily_plan);
    member_manager.GetCurrentMember()->SetWeeklyExercisePlanPeriod(QDate::currentDate(), QDate::currentDate().addMonths(2));
    member_manager.SaveChangesOnCurrentMember();*/

    qDebug() << "name: " << current_member->GetName();
    qDebug() << "age: " << current_member->GetAge();
    qDebug() << "chest: " << current_member->GetChest();
    qDebug() << "subs: " << current_member->HasSubscription();
    qDebug() << "remaining: " << current_member->GetRemainingDays();
    qDebug() << "cooldown: " << current_member->GetWeeklyExercisePlan().back().GetCooldownPeriod();
    qDebug() << "name: " << Exercise::toString(current_member->GetWeeklyExercisePlan().back().GetDailyExercisePlan().back()->GetName());

    ///////////////////////////////////////
}

MainWindow::~MainWindow()
{
    delete ui;
}
