#include "../inc/exercise.h"

namespace Exercise
{

Exercise::Exercise(ExerciseType type, ExerciseName name, short set,
                   short repeat, short cooldown_period, const QDate &last_done_date)
    : type_(type), name_(name), set_(set), repeat_(repeat),
    cooldown_period_(cooldown_period), last_done_date_(last_done_date) {}

void Exercise::MarkExerciseDone(){ last_done_date_ = QDate::currentDate(); }

bool Exercise::IsReady(){
    if(QDate::currentDate() > last_done_date_.addDays(cooldown_period_))
        return true;
    else
        return false;
}

ExerciseType Exercise::GetType() const { return type_; }
ExerciseName Exercise::GetName() const { return name_; }
short Exercise::GetSet() const { return set_; }
short Exercise::GetRepeat() const { return repeat_; }
short Exercise::GetCoolDownPeriod() const { return cooldown_period_; }
QDate Exercise::GetLastDoneDate() const { return last_done_date_; }

QJsonObject Exercise::toJson() const {
    QJsonObject json;
    json["type"] = ToString(type_);
    json["name"] = ToString(name_);
    json["set"] = set_;
    json["repeat"] = repeat_;
    json["cooldown_period"] = cooldown_period_;
    json["last_done_date"] = last_done_date_.toString(Qt::ISODate);
    return json;
}

}

