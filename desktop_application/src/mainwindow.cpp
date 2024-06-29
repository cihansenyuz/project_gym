#include "../inc/mainwindow.h"
#include "../ui/ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //////// TEST & DEBUG SECTION /////////

    /*if(member_manager.SetCurrentMemberByName("Alice")){
        qDebug() << "current selected member: " << member_manager.GetCurrentMember()->GetName();

        //member_manager.GetCurrentMember()->SetAge(22);
        //member_manager.SaveChangesOnCurrentMember();
    }
    else
        qDebug() << "no member found";*/

    member_manager.SetCurrentMemberByName("cihan");
    /*member_manager.GetCurrentMember()->ClearWeeklyExercisePlan();
    member_manager.SaveChangesOnCurrentMember();

    DailyExercisePlan daily_plan;
    CardioWorkout *exercise = new CardioWorkout(ExerciseType::Cardio, ExerciseName::TreadmillRunning, 20);
    CardioWorkout *exercise2 = new CardioWorkout(ExerciseType::Cardio, ExerciseName::StairClimber, 10);
    StrengthWorkout *exercise3 = new StrengthWorkout(ExerciseType::Chest, ExerciseName::BenchPress, 3, 8);

    daily_plan.AddNewExercise(exercise);
    daily_plan.AddNewExercise(exercise2);
    daily_plan.AddNewExercise(exercise3);
    daily_plan.SetCooldownPeriod(2);

    member_manager.GetCurrentMember()->AddNewDailyExercisePlan(daily_plan);
    member_manager.GetCurrentMember()->SetWeeklyExercisePlanPeriod(QDate::currentDate(), QDate::currentDate().addMonths(1));
    member_manager.SaveChangesOnCurrentMember();*/

    qDebug() << "chest: " << member_manager.GetCurrentMember()->GetChest();
    qDebug() << "subs: " << member_manager.GetCurrentMember()->HasSubscription();
    qDebug() << "remaining: " << member_manager.GetCurrentMember()->GetRemainingDays();
    qDebug() << "cooldown: " << member_manager.GetCurrentMember()->GetWeeklyExercisePlan().back().GetCooldownPeriod();
    qDebug() << "name: " << Exercise::toString(member_manager.GetCurrentMember()->GetWeeklyExercisePlan().back().GetDailyExercisePlan().back()->GetName());

    ///////////////////////////////////////
}

MainWindow::~MainWindow()
{
    delete ui;
}
