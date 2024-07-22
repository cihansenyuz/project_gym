#include "../inc/network/httpmanager.h"
#include "../inc/gui/logindialog.h"
#include "../inc/gui/mainwindow.h"

#include <QApplication>
#include <memory>

#define USE_LOCAL_HOST 0 // 1: local host, 0: google cloud

int main(int argc, char *argv[])
{
    QApplication application(argc, argv);
    std::shared_ptr<HttpManager> http_manager = std::make_shared<HttpManager>();
    if (!http_manager) {
        qWarning("http_manager is nullptr before login");
    }else
        qWarning("http_manager is not nullptr before login");
    LoginDialog dialog(http_manager);
    dialog.show();
    std::shared_ptr<MainWindow> window;

    auto CreateMainWindow = [&](bool success){
        qDebug() << "create";
        if(success){qDebug() << "create";
            window = std::make_shared<MainWindow>(http_manager);}
    };

    QObject::connect(http_manager.get(), &HttpManager::LoginAttempt, CreateMainWindow);

    return application.exec();
}
