#include "../inc/mainwindow.h"
#include "../ui/ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //////// TEST & DEBUG SECTION /////////

    if(member_manager.SetCurrentMemberByName("Chris Johnson")){
        qDebug() << "current selected member: " << member_manager.GetCurrentMember()->GetName();
        //member_manager.DeleteCurrentMember();
    }
    else
        qDebug() << "no member found";

    ///////////////////////////////////////
}

MainWindow::~MainWindow()
{
    delete ui;
}
