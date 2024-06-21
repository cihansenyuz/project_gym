#include "../inc/mainwindow.h"
#include "../ui/ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //////// TEST & DEBUG SECTION /////////

    if(member_manager.GetMemberByName("John Doe")){
        qDebug() << "leg: " << member_manager.current_member->GetLeg(1);
        qDebug() << "taken date: " << member_manager.current_member->GetTakenDate(1);
    }
    else
        qDebug() << "no member found";
    ///////////////////////////////////////
}

MainWindow::~MainWindow()
{
    delete ui;
}
