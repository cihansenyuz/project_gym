#include "../inc/mainwindow.h"
#include "../ui/ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //////// TEST & DEBUG SECTION /////////

    if(member_manager.GetMemberByName("John Doe")){
        qDebug() << "name: " << member_manager.GetCurrentMember()->GetName();
        qDebug() << "measurement taken date: " << member_manager.GetCurrentMember()->GetTakenDate(1);
    }
    else
        qDebug() << "no member found";

    ///////////////////////////////////////
}

MainWindow::~MainWindow()
{
    delete ui;
}
