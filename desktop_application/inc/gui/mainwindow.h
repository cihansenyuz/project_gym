#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtNetwork>
#include "../member/member.h"
#include "../json/membermanager.h"
#include "../network/httpmanager.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(HttpManager *http_manager, QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    HttpManager *http_manager_;
    MemberManager member_manager{http_manager_};
};
#endif // MAINWINDOW_H
