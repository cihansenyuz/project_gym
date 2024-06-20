#include "../inc/measurement.h"

Measurement::Measurement(float weight, float shoulder, float chest,
                         float arm, float belly, float hip, float leg)
    : weight_(weight), shoulder_(shoulder), chest_(chest),
      arm_(arm), belly_(belly), hip_(hip), leg_(leg) {}

float Measurement::getWeight() const { return weight_; }
float Measurement::getShoulder() const { return shoulder_; }
float Measurement::getChest() const { return chest_; }
float Measurement::getArm() const { return arm_; }
float Measurement::getBelly() const { return belly_; }
float Measurement::getHip() const { return hip_; }
float Measurement::getLeg() const { return leg_; }
QDate Measurement::getTakenDate() const { return taken_date_; }

void Measurement::setWeight(float weight) { weight_ = weight; }
void Measurement::setShoulder(float shoulder) { shoulder_ = shoulder; }
void Measurement::setChest(float chest) { chest_ = chest; }
void Measurement::setArm(float arm) { arm_ = arm; }
void Measurement::setBelly(float belly) { belly_ = belly; }
void Measurement::setHip(float hip) { hip_ = hip; }
void Measurement::setLeg(float leg) { leg_ = leg; }
