#include "../inc/mainwindow.h"
#include "../ui/ui_mainwindow.h"
#include "../inc/exerciseplan.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //////// TEST & DEBUG SECTION /////////

    /*if(member_manager.SetCurrentMemberByName("Jessica Lee")){
        qDebug() << "current selected member: " << member_manager.GetCurrentMember()->GetName();
        member_manager.GetCurrentMember()->EndSubscription();
        member_manager.SaveChangesOnCurrentMember();
    }
    else
        qDebug() << "no member found";*/

    ExercisePlan plan;
    plan.SetTargetDate(QDate(2024, 6, 30));

    Exercise::Exercise_t first;
    first.name = Exercise::latPulldown;
    first.type = Exercise::back;
    first.set = 3;
    first.repeat = 8;
    plan.AddNewExercise(first, 2);

    Exercise::Exercise_t second;
    second.name = Exercise::benchPress;
    second.type = Exercise::chest;
    second.set = 3;
    second.repeat = 10;
    plan.AddNewExercise(second, 3);

    plan.PrintPlan();

    ///////////////////////////////////////
}

MainWindow::~MainWindow()
{
    delete ui;
}
