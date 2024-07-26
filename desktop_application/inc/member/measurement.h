/**
  ******************************************************************************
  * @file    measurement.hpp
  * @author  Cihan Senyuz
  * @date    19.06.2024
  * @brief   Header for measurement.cpp file.
  *                 Stores physical measurements of a member including arm, belly,
  *          chest, hip, leg, shoulder, and weight, taken on a specific date.
  *          Provides methods for managing and accessing measurement data.
  *
  ******************************************************************************
  */

#ifndef MEASUREMENT_H
#define MEASUREMENT_H

#include <QJsonObject>

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
