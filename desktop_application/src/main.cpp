#include "../inc/gui/logindialog.h"
#include "../inc/gui/mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication application(argc, argv);
    HttpManager *http_manager = new HttpManager;
    LoginDialog dialog(http_manager);
    dialog.show();
    MainWindow window(http_manager);

    return application.exec();
}
