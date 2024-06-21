#ifndef MEASUREMENT_H
#define MEASUREMENT_H

#include <QDate>
#include <QJsonObject>
#include <QJsonArray>

class Measurement
{
public:
    Measurement() = default;
    Measurement(QDate date, float weight, float shoulder, float chest,
                float arm, float belly, float hip, float leg);
    float GetWeight() const;
    float GetShoulder() const;
    float GetChest() const;
    float GetArm() const;
    float GetBelly() const;
    float GetHip() const;
    float GetLeg() const;
    QDate GetTakenDate() const;

    QJsonObject toJson() const;

protected:
    void SetWeight(float weight);
    void SetShoulder(float shoulder);
    void SetChest(float chest);
    void SetArm(float arm);
    void SetBelly(float belly);
    void SetHip(float hip);
    void SetLeg(float leg);
    void SetTakenDate(QDate taken_date);

private:
    QDate taken_date_;
    float weight_;
    float shoulder_;
    float chest_;
    float arm_;
    float belly_;
    float hip_;
    float leg_;
};

#endif // MEASUREMENT_H
