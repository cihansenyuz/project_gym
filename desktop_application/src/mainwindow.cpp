#include "../inc/mainwindow.h"
#include "../ui/ui_mainwindow.h"
#include "../inc/exerciseplan.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //////// TEST & DEBUG SECTION /////////

    if(member_manager.SetCurrentMemberByName("John Doe")){
        qDebug() << "current selected member: " << member_manager.GetCurrentMember()->GetName();

        //std::map<QString, Exercise::Exercise_t> updated_plan = member_manager.GetCurrentMember()->GetWeeklyPlan();
        //updated_plan["T+2"].type = Exercise::chest;
        //member_manager.GetCurrentMember()->SetWeeklyPlan(updated_plan);
        member_manager.GetCurrentMember()->PrintPlan();
        member_manager.GetCurrentMember()->SetAge(30);
        member_manager.SaveChangesOnCurrentMember();
    }
    else
        qDebug() << "no member found";

    ///////////////////////////////////////
}

MainWindow::~MainWindow()
{
    delete ui;
}
