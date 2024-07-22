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

    connect(ui->get_button, &QPushButton::clicked,
            this, &MainWindow::OnGetButtonClicked);
    connect(ui->save_changes_action, &QAction::triggered,
            this, &MainWindow::OnSaveChangesAction);
    connect(ui->delete_action, &QAction::triggered,
            this, &MainWindow::OnDeleteAction);

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

    ///////////////////////////////////////
}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::OnMemberDataFetched(QJsonArray* fetched_data){
    member_manager.SetMemberArrayData(fetched_data);
    if(member_manager.GetMemberArrayData()->isEmpty())
        ui->message_text_browser->append("Welcome, this is your first time,"
                                            "so no member registered in the system."
                                            "\n You can start registering members "
                                            "using 'Manage Database' menu on the menu bar");
    this->show();
}

void MainWindow::OnGetButtonClicked(){
    current_member = member_manager.GetMember(ui->member_name_line_edit->text());
    if(current_member){
        ui->message_text_browser->append("Member info has gotten: "
                                         + current_member->GetName());
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
        }

        FillExercisePlanTable();
    }
    else
        ui->message_text_browser->append("No member found!");
}

void MainWindow::OnSaveChangesAction(){
    http_manager_->PushMemberJsonData(member_manager.GetMemberArrayData());
}

void MainWindow::OnDeleteAction(){
    if(!current_member){
        message_dialog = std::make_unique<InfoDialog>("No member viewed,\nPlease, use Get button first");
        return;
    }
    QString member_name = current_member->GetName();
    member_manager.DeleteMember(member_name);
    message_dialog = std::make_unique<InfoDialog>("Member '"+member_name+"' is deleted");
}

void MainWindow::FillExercisePlanTable(){
    DeleteExercisePlanTable();

    std::vector<DailyExercisePlan> weekly_exercise_plan = current_member->GetWeeklyExercisePlan();
    if(weekly_exercise_plan.size() == 0)
        return;

    exercise_day_tabs = std::make_unique<QTabWidget>();

    int day_no = 1;
    for(auto &daily_plan : weekly_exercise_plan){
        QWidget *new_tab = new QWidget;
        QVBoxLayout *exercise_day_layout = new QVBoxLayout(new_tab);
        QTableWidget *exercise_day_table = new QTableWidget(5, daily_plan.GetDailyExercisePlan().size(), new_tab);
        exercise_day_table->setVerticalHeaderLabels(QStringList{"Type",
                                                                "Name",
                                                                "Sets",
                                                                "Repeats",
                                                                "Durition"});
        exercise_day_layout->addWidget(exercise_day_table);
        new_tab->setLayout(exercise_day_layout);
        exercise_day_tabs->addTab(new_tab, QString("Day %1\nCooldown: %2days").arg(day_no++).arg(daily_plan.GetCooldownPeriod()));

        std::vector<Exercise*> all_exercises = daily_plan.GetDailyExercisePlan();
        for(int i=0; i < all_exercises.size(); i++){
            QTableWidgetItem *header_item = new QTableWidgetItem(QString("Exercise %1").arg(i+1));
            exercise_day_table->setHorizontalHeaderItem(i, header_item);

            ExerciseType type = all_exercises[i]->GetType();
            QTableWidgetItem *item_type = new QTableWidgetItem(Exercise::toString(type));
            exercise_day_table->setItem(0, i, item_type);
            QTableWidgetItem *item_name = new QTableWidgetItem(Exercise::toString(all_exercises[i]->GetName()));
            exercise_day_table->setItem(1, i, item_name);
            if(type == Cardio){
                CardioWorkout* casted_exercise = dynamic_cast<CardioWorkout*>(all_exercises[i]);
                QTableWidgetItem *item_durition = new QTableWidgetItem(QString::number(casted_exercise->GetDurition()));
                exercise_day_table->setItem(4, i, item_durition);
            }
            else{
                StrengthWorkout* casted_exercise = dynamic_cast<StrengthWorkout*>(all_exercises[i]);
                QTableWidgetItem *item_set = new QTableWidgetItem(QString::number(casted_exercise->GetSet()));
                exercise_day_table->setItem(2, i, item_set);
                QTableWidgetItem *item_repeat = new QTableWidgetItem(QString::number(casted_exercise->GetRepeat()));
                exercise_day_table->setItem(3, i, item_repeat);
            }
        }
    }

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

void MainWindow::NewDialog(const QString &message, const QString &title){
    if(message_dialog)
        message_dialog.reset(nullptr);
    message_dialog = std::make_unique<InfoDialog>(message, title);
}
