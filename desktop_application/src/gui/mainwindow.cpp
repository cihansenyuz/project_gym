#include "../../inc/gui/mainwindow.h"
#include "../../ui/ui_mainwindow.h"

MainWindow::MainWindow(HttpManager *http_manager, QWidget *parent)
    : http_manager_(http_manager), QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(http_manager_, &HttpManager::MemberJsonFetched,
            this, &MainWindow::OnMemberDataFetched);
    http_manager_->FetchMemberJsonData();

    connect(ui->get_button, &QPushButton::clicked,
            this, &MainWindow::OnGetButtonClicked);

    //////// TEST & DEBUG SECTION /////////

    /*DailyExercisePlan daily_plan;
    CardioWorkout *exercise = new CardioWorkout(ExerciseType::Cardio, ExerciseName::TreadmillRunning, 20);
    CardioWorkout *exercise2 = new CardioWorkout(ExerciseType::Cardio, ExerciseName::StairClimber, 10);
    StrengthWorkout *exercise3 = new StrengthWorkout(ExerciseType::Chest, ExerciseName::BenchPress, 3, 8);

    daily_plan.AddNewExercise(exercise);
    daily_plan.AddNewExercise(exercise2);
    daily_plan.AddNewExercise(exercise3);
    daily_plan.SetCooldownPeriod(3);

    member_manager.SaveChangesOnCurrentMember();*/

    ///////////////////////////////////////
}

MainWindow::~MainWindow(){
    delete http_manager_;
    delete ui;
}

void MainWindow::OnMemberDataFetched(){
    member_manager.LoadFromFile();
    this->show();
}

void MainWindow::OnGetButtonClicked(){
    Member* current_member = member_manager.GetMember(ui->member_name_line_edit->text());
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
    }
    else
        ui->message_text_browser->append("No member found!");
}
