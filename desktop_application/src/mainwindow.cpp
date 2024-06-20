#include "../inc/mainwindow.h"
#include "../ui/ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //////// TEST & DEBUG SECTION /////////
    Measurement test_measurement(1, 2, 3, 4, 5, 6, 7);
    Member test_member("test", 20, test_measurement);
    //test_member.AddMeasurement(test_measurement);

    ///////////////////////////////////////
}

MainWindow::~MainWindow()
{
    delete ui;
}
