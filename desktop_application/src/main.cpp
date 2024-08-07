#include "../inc/network/httpmanager.h"
#include "../inc/gui/logindialog.h"
#include "../inc/gui/mainwindow.h"

#include <QApplication>
#include <memory>

#define DEV_MODE_SKIP_LOGIN 1 // 0: ask login, 1: skip

#if DEV_MODE_SKIP_LOGIN
#pragma message("login dialog will be skipped")
#endif

#if DEV_MODE_USE_PRETAKEN_TOKEN
#pragma message("pretaken token will be used: be sure it's valid")
#endif

#if DEV_MODE_USE_LOCAL_HOST
#pragma message("api URL is local host")
#else
#pragma message("api URL is gCloud")
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
#if DEV_MODE_SKIP_LOGIN
    dialog.close();
    CreateMainWindow(true);
#endif
    return application.exec();
}
