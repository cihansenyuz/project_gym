#include "../../inc/member/measurement.h"

Measurement::Measurement(QDate date, float weight, float shoulder, float chest,
                         float arm, float belly, float hip, float leg)
    : taken_date_(date), weight_(weight), shoulder_(shoulder), chest_(chest),
      arm_(arm), belly_(belly), hip_(hip), leg_(leg) {}

float Measurement::GetWeight() const { return weight_; }
float Measurement::GetShoulder() const { return shoulder_; }
float Measurement::GetChest() const { return chest_; }
float Measurement::GetArm() const { return arm_; }
float Measurement::GetBelly() const { return belly_; }
float Measurement::GetHip() const { return hip_; }
float Measurement::GetLeg() const { return leg_; }
QDate Measurement::GetTakenDate() const { return taken_date_; }

QJsonObject Measurement::toJson() const
{
    QJsonObject json;
    json["weight"] = weight_;
    json["shoulder"] = shoulder_;
    json["chest"] = chest_;
    json["arm"] = arm_;
    json["belly"] = belly_;
    json["hip"] = hip_;
    json["leg"] = leg_;
    json["taken_date"] = taken_date_.toString(Qt::ISODate);

    return json;
}
