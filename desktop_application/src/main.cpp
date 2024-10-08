#include "../inc/network/httpmanager.h"
#include "../inc/gui/logindialog.h"
#include "../inc/gui/mainwindow.h"

#include <QApplication>
#include <memory>

#ifndef DEV_MODE
    #define DEV_MODE 0 // 0: ask login, 1: skip
#endif

int main(int argc, char *argv[])
{
    QApplication application(argc, argv);
    std::shared_ptr<HttpManager> http_manager = std::make_shared<HttpManager>();
    LoginDialog dialog(http_manager);
    dialog.show();
    std::shared_ptr<MainWindow> window;

    auto CreateMainWindow = [&](bool success){
        if(success)
            window = std::make_shared<MainWindow>(http_manager);
    };

    QObject::connect(http_manager.get(), &HttpManager::LoginAttempt, CreateMainWindow);
#if DEV_MODE
    dialog.close();
    CreateMainWindow(true);
#endif
    return application.exec();
}
