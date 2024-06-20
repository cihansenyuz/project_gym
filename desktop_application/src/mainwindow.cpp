#include "../inc/mainwindow.h"
#include "../ui/ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //////// TEST & DEBUG SECTION /////////

    Measurement test_measurement(15, 25, 35, 45, 55, 65, 75);
    Measurement test_measurement2(115, 225, 335, 445, 555, 665, 775);
    Member test_member("test3", 40, test_measurement);
    /*test_member.AddMeasurement(test_measurement2);
    test_member.SetSubscriptionStartDate(QDate::currentDate(), QDate::currentDate());*/

    member_manager.SaveMemberToJson(test_member);

    ///////////////////////////////////////
}

MainWindow::~MainWindow()
{
    delete ui;
}
