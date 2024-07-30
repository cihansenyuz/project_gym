/**
  ******************************************************************************
  * @file    mainwindow.hpp
  * @author  Cihan Senyuz
  * @date    10.07.2024
  * @brief   Header for MainWindow class.
  *          This file contains the definition of the MainWindow class, which
  *          represents the main window of the application. The class includes methods
  *          for managing and interacting with various dialogs and network operations,
  *          as well as handling user actions related to member data, exercise plans,
  *          and more.
  *
  ******************************************************************************
  */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include "../member/member.h"
#include "../json/membermanager.h"
#include "../network/httpmanager.h"
#include "../gui/infodialog.h"
#include "../gui/registerdialog.h"
#include "../gui/newmeasurementsdialog.h"
#include "../gui/components/exerciseweekview.h"
#include "../gui/exerciseplandialog.h"

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
    void OnRegisterActionTriggered();
    void OnSaveChangesActionTriggered();
    void OnDeleteActionTriggered();
    void OnAddNewMeasurementsActionTriggered();
    void OnNewMemberCreated(const std::unique_ptr<Member> &new_member);
    void OnNewMeasurementsAdded(const Measurement &new_measurements);
    void OnNewWeeklyExerciseActionTriggered();
    void OnNewWeeklyPlanReadyCreated(const std::vector<DailyExercisePlan> &new_weekly_exercise_plan,
                                     const QDate &start, const QDate &end);

private:
    void ClearViewedMemberInfos();
    void FillExercisePlanTable();
    void DeleteExercisePlanTable();
    void NewDialog(const QString &message, const QString &title = "", bool is_modal = true);
    bool IsCurrentMemberSelected();

    Ui::MainWindow *ui;
    std::shared_ptr<HttpManager> http_manager_;
    MemberManager member_manager;
    std::unique_ptr<Member> current_member;
    std::unique_ptr<ExerciseWeekView> exercise_day_tabs;
    std::unique_ptr<InfoDialog> message_dialog;
    std::unique_ptr<RegisterDialog> register_dialog;
    std::unique_ptr<NewMeasurementsDialog> measurements_dialog;
    std::unique_ptr<ExercisePlanDialog> new_exercise_plan_dialog;
};
#endif // MAINWINDOW_H
