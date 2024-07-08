#include "../inc/gui/logindialog.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication application(argc, argv);
    LoginDialog dialog;
    dialog.show();
    return application.exec();
}
