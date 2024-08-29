#include "../../inc/gui/mainwindow.h"
#include "../../ui/ui_mainwindow.h"

MainWindow::MainWindow(std::shared_ptr<HttpManager> &http_manager, QWidget *parent)
    : http_manager_(http_manager), QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(http_manager_.get(), &HttpManager::MemberJsonFetched,
            this, &MainWindow::OnMemberDataFetched);
    http_manager_->FetchMemberJsonData();

    connect(ui->register_action, &QAction::triggered,
            this, &MainWindow::OnRegisterActionTriggered);
    connect(ui->get_button, &QPushButton::clicked,
            this, &MainWindow::OnGetButtonClicked);
    connect(ui->save_changes_action, &QAction::triggered,
            this, &MainWindow::OnSaveChangesActionTriggered);
    connect(ui->delete_action, &QAction::triggered,
            this, &MainWindow::OnDeleteActionTriggered);
    connect(ui->new_measurements_action, &QAction::triggered,
            this, &MainWindow::OnAddNewMeasurementsActionTriggered);
    connect(ui->new_weekly_exercise_plan_action, &QAction::triggered,
            this, &MainWindow::OnNewWeeklyExerciseActionTriggered);

    //////// TEST & DEBUG SECTION /////////

    /*DailyExercisePlan daily_plan;
    CardioWorkout *exercise = new CardioWorkout(ExerciseType::Cardio, ExerciseName::TreadmillRunning, 20);
    CardioWorkout *exercise2 = new CardioWorkout(ExerciseType::Cardio, ExerciseName::StairClimber, 10);
    StrengthWorkout *exercise3 = new StrengthWorkout(ExerciseType::Chest, ExerciseName::BenchPress, 3, 8);

    daily_plan.AddNewExercise(exercise);
    daily_plan.AddNewExercise(exercise2);
    daily_plan.AddNewExercise(exercise3);
    daily_plan.SetCooldownPeriod(3);*/

    //current_member->SetAge(20);
    //member_manager.SaveChangesOnMember(*current_member);

    /*if(register_dialog)
        qDebug() << "register is not null";
    else
        qDebug() << "register is null";*/

    ///////////////////////////////////////
}

MainWindow::~MainWindow(){
    delete ui;
}

bool MainWindow::IsCurrentMemberSelected(){
    if(!current_member){
        NewDialog("No member viewed,\nPlease, use Get button first", "Error!");
        return false;
    }
    return true;
}

void MainWindow::OnMemberDataFetched(const std::unique_ptr<QJsonArray> &fetched_data){
    member_manager.SetMemberArrayData(fetched_data);
    if(member_manager.GetMemberArrayData()->isEmpty())
        ui->message_text_browser->append("Welcome, this is your first time,"
                                            "so no member registered in the system."
                                            "\n You can start registering members "
                                            "using 'Manage Database' menu on the menu bar");
    this->show();
}

void MainWindow::OnGetButtonClicked(){
    current_member = member_manager.GetMember(ui->member_id_line_edit->text());

    //////// TEST & DEBUG SECTION /////////

    /*current_member->Pay();
    member_manager.SaveChangesOnMember(*current_member);*/

    ///////////////////////////////////////

    if(current_member){
        ui->message_text_browser->append("Member info has gotten: "
                                         + current_member->GetId());
        ui->name_label->setText(current_member->GetName());
        ui->age_label->setText(QString::number(current_member->GetAge()));
        //ui->gender_label->setText();
        //ui->phone_label->setText();

        if(current_member->GetAllMeasurements().size()){
        Measurement last = current_member->GetLastMeasurements();
            ui->weight_label->setText(QString::number(last.GetWeight()));
            ui->shoulder_label->setText(QString::number(last.GetShoulder()));
            ui->chest_label->setText(QString::number(last.GetChest()));
            ui->arm_label->setText(QString::number(last.GetArm()));
            ui->belly_label->setText(QString::number(last.GetBelly()));
            ui->hip_label->setText(QString::number(last.GetHip()));
            ui->leg_label->setText(QString::number(last.GetLeg()));
            ui->taken_date_label->setText(last.GetTakenDate().toString(Qt::ISODate));
        }

        if(current_member->GetAllArchivedSubscriptions().size()
            || current_member->HasSubscription()){
            ui->sub_start_date_label->setText(current_member->GetSubscriptionStartDate().toString(Qt::ISODate));
            ui->sub_end_date_label->setText(current_member->GetSubscriptionEndDate().toString(Qt::ISODate));
            ui->remaining_months_label->setText(QString::number(current_member->GetSubscriptionEndDate().month()
                                                                    - QDate::currentDate().month()));

            ui->total_price_label->setText(QString::number(current_member->GetPrice()));
            ui->payment_label->setText(QString::number(current_member->OneInstallmentQuantity()));
            ui->remaining_payment_label->setText(QString::number(current_member->RemainingPaymentsTotal()));
            ui->installments_label->setText(QString::number(current_member->GetNumOfInstallments()));
            ui->installments_remaining_label->setText(QString::number(current_member->RemainingInstallmentQuantity()));
        }

        FillExercisePlanTable();
    }
    else
        ui->message_text_browser->append("No member found!");
}

void MainWindow::OnSaveChangesActionTriggered(){
    http_manager_->PushMemberJsonData(member_manager.GetMemberArrayData());
}

void MainWindow::OnDeleteActionTriggered(){
    if(!IsCurrentMemberSelected())
        return;
    QString member_id = current_member->GetId();
    member_manager.DeleteMember(member_id);
    NewDialog("Member '"+member_id+"' is deleted", "Success!");
    ClearViewedMemberInfos();
}

void MainWindow::FillExercisePlanTable(){
    DeleteExercisePlanTable();

    std::vector<DailyExercisePlan> weekly_exercise_plan = current_member->GetWeeklyExercisePlan();
    if(weekly_exercise_plan.size() == 0)
        return;

    exercise_day_tabs = std::make_unique<ExerciseWeekView>(weekly_exercise_plan);

    ui->verticalLayout_4->addWidget(exercise_day_tabs.get());
    ui->exercise_plan_group->setLayout(ui->verticalLayout_4);
}

void MainWindow::DeleteExercisePlanTable() {
    if(!exercise_day_tabs)
        return;

    while (exercise_day_tabs->count() > 0) {
        QWidget *tab = exercise_day_tabs->widget(0);
        if (tab) {
            QTableWidget *tableWidget = tab->findChild<QTableWidget *>();
            if (tableWidget) {
                tableWidget->clear();
            }
        }
        exercise_day_tabs->removeTab(0);
        delete tab;
    }
}

void MainWindow::NewDialog(const QString &message, const QString &title, bool is_modal){
    if(message_dialog)
        message_dialog.reset(nullptr);
    message_dialog = std::make_unique<InfoDialog>(message, title, this);
    if(is_modal)
        message_dialog->exec();
    else
        message_dialog->show();
}

void MainWindow::OnRegisterActionTriggered(){
    register_dialog = std::make_unique<RegisterDialog>(this);
    connect(register_dialog.get(), &RegisterDialog::MemberCreated,
            this, &MainWindow::OnNewMemberCreated);
    register_dialog->exec();
}

void MainWindow::OnNewMemberCreated(const std::unique_ptr<Member> &new_member){
    member_manager.GenerateId(*new_member);
    member_manager.RegisterNewMember(*new_member);
    ui->message_text_browser->append("New member registered, ID: "+new_member->GetId());
    /*if(register_dialog){
        qDebug() << "register reset";
        register_dialog.reset(nullptr);
    }*/
}

void MainWindow::OnAddNewMeasurementsActionTriggered(){
    measurements_dialog = std::make_unique<NewMeasurementsDialog>(this);
    connect(measurements_dialog.get(), &NewMeasurementsDialog::NewMeasurements,
            this, &MainWindow::OnNewMeasurementsAdded);
    measurements_dialog->exec();
}

void MainWindow::OnNewMeasurementsAdded(const Measurement &new_measurements){
    current_member->AddMeasurement(new_measurements);
    member_manager.SaveChangesOnMember(*current_member);
    ui->message_text_browser->append("New measurements recorded for the current member");
}

void MainWindow::ClearViewedMemberInfos(){
    // info view
    ui->member_id_line_edit->clear();
    ui->name_label->clear();
    ui->age_label->clear();
    ui->gender_label->clear();
    ui->phone_label->clear();
    // subscription view
    ui->sub_start_date_label->clear();
    ui->sub_end_date_label->clear();
    ui->remaining_months_label->clear();
    // measurements view
    ui->shoulder_label->clear();
    ui->chest_label->clear();
    ui->arm_label->clear();
    ui->belly_label->clear();
    ui->hip_label->clear();
    ui->leg_label->clear();
    ui->weight_label->clear();
    ui->taken_date_label->clear();
    // payment view
    ui->total_price_label->clear();
    ui->remaining_payment_label->clear();
    ui->installments_label->clear();
    ui->installments_remaining_label->clear();
    ui->payment_label->clear();
    // exercise plan view
    DeleteExercisePlanTable();
}

void MainWindow::OnNewWeeklyExerciseActionTriggered(){
    if(!IsCurrentMemberSelected())
        return;

    new_exercise_plan_dialog = std::make_unique<ExercisePlanDialog>(this);
    connect(new_exercise_plan_dialog.get(), &ExercisePlanDialog::NewWeeklyPlanReady,
            this, &MainWindow::OnNewWeeklyPlanReadyCreated);
    new_exercise_plan_dialog->exec();
}

void MainWindow::OnNewWeeklyPlanReadyCreated(const std::vector<DailyExercisePlan> &new_weekly_exercise_plan,
                                             const QDate &start, const QDate &end){
    current_member->EndExercisePlan();
    current_member->SetWeeklyExercisePlan(new_weekly_exercise_plan);
    current_member->SetWeeklyExercisePlanPeriod(start, end);
    member_manager.SaveChangesOnMember(*current_member);
    ui->message_text_browser->append("New weekly exercise plan saved for the current member");
}
