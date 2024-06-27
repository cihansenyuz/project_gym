#ifndef CARDIOWORKOUT_H
#define CARDIOWORKOUT_H

#include "exercise.h"
#include <QJsonObject>

class CardioWorkout : public Exercise
{
public:
    CardioWorkout() = delete;
    CardioWorkout(ExerciseType type, ExerciseName name, short durition);
    QJsonObject toJson() const override;

    short GetDurition() const;

private:
    short durition_;
};

#endif // CARDIOWORKOUT_H
