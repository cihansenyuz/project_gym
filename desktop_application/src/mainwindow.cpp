#include "../inc/mainwindow.h"
#include "../ui/ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //////// TEST & DEBUG SECTION /////////

    if(member_manager.SetCurrentMemberByName("John Doe")){
        qDebug() << "name: " << member_manager.GetCurrentMember()->GetName();
    }
    else
        qDebug() << "no member found";

    ///////////////////////////////////////
}

MainWindow::~MainWindow()
{
    delete ui;
}
