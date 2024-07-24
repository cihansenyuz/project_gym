#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtNetwork>
#include <QTableWidget>
#include <memory>

#include "../member/member.h"
#include "../json/membermanager.h"
#include "../network/httpmanager.h"
#include "../gui/infodialog.h"
#include "../gui/registerdialog.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;

}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(std::shared_ptr<HttpManager> &http_manager, QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void OnMemberDataFetched(const std::unique_ptr<QJsonArray> &fetched_data);
    void OnGetButtonClicked();
    void OnRegisterAction();
    void OnSaveChangesAction();
    void OnDeleteAction();
    void OnNewMemberCreated(const std::unique_ptr<Member> &new_member);

private:
    void FillExercisePlanTable();
    void DeleteExercisePlanTable();
    void NewDialog(const QString &message, const QString &title = "");

    Ui::MainWindow *ui;
    std::shared_ptr<HttpManager> http_manager_;
    MemberManager member_manager;
    std::unique_ptr<Member> current_member;
    std::unique_ptr<QTabWidget> exercise_day_tabs;
    std::unique_ptr<InfoDialog> message_dialog;
    std::unique_ptr<RegisterDialog> register_dialog;
};
#endif // MAINWINDOW_H
