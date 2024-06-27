#ifndef STRENGTHWORKOUT_H
#define STRENGTHWORKOUT_H

#include "exercise.h"
#include <QJsonObject>

class StrengthWorkout : public Exercise
{
public:
    StrengthWorkout() = delete;
    StrengthWorkout(ExerciseType type, ExerciseName name, short set, short repeat);
    QJsonObject toJson() const override;

    short GetSet() const;
    short GetRepeat() const;

private:
    short set_;
    short repeat_;
};

#endif // STRENGTHWORKOUT_H
