#include "../inc/exercise.h"

ExerciseType Exercise::fromStringExerciseType(const QString &str) {
    if (str == "cardio") return cardio;
    else if (str == "shoulder") return shoulder;
    else if (str == "chest") return chest;
    else if (str == "back") return back;
    else if (str == "arm") return arm;
    else if (str == "leg") return leg;
    else return unknownType;
}

QString Exercise::ToString(const ExerciseType &type){
    switch(type) {
    case cardio: return "cardio";
    case shoulder: return "shoulder";
    case chest: return "chest";
    case back: return "back";
    case arm: return "arm";
    case leg: return "leg";
    default: return "unknownType";
    }
}

/*void Exercise::MarkExerciseDone(){ last_done_date_ = QDate::currentDate(); }

bool Exercise::IsReady(){
    if(QDate::currentDate() > last_done_date_.addDays(cooldown_period_))
        return true;
    else
        return false;
}*/

ExerciseType Exercise::GetType() const { return type_; }
/*ExerciseName Exercise::GetName() const { return name_; }
short Exercise::GetSet() const { return set_; }
short Exercise::GetRepeat() const { return repeat_; }
short Exercise::GetCoolDownPeriod() const { return cooldown_period_; }
QDate Exercise::GetLastDoneDate() const { return last_done_date_; }*/


