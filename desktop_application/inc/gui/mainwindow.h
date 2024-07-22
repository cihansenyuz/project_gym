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
    void OnMemberDataFetched(QJsonArray* fetched_data);
    void OnGetButtonClicked();
    void OnSaveChangesAction();
    void OnDeleteAction();

private:
    void FillExercisePlanTable();
    void DeleteExercisePlanTable();
    void NewDialog(const QString &message, const QString &title = "");

    Ui::MainWindow *ui;
    std::shared_ptr<HttpManager> http_manager_;
    MemberManager member_manager;
    std::unique_ptr<Member> current_member;
    QTabWidget *exercise_day_tab{nullptr};
    std::unique_ptr<InfoDialog> message_dialog;
};
#endif // MAINWINDOW_H
