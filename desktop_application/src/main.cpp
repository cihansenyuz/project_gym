#include "../inc/network/httpmanager.h"
#include "../inc/gui/logindialog.h"
#include "../inc/gui/mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication application(argc, argv);
    HttpManager *http_manager = new HttpManager;
    LoginDialog dialog(http_manager);
    dialog.show();

    auto CreateMainWindow = [&](bool success){
        if(success)
            MainWindow *window = new MainWindow(http_manager);
    };

    QObject::connect(http_manager, &HttpManager::LoginAttempt, CreateMainWindow);

    return application.exec();
}
