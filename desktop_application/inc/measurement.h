#ifndef MEASUREMENT_H
#define MEASUREMENT_H

#include <QDate>

class Measurement
{
public:
    Measurement(float weight, float shoulder, float chest,
                float arm, float belly, float hip, float leg);
    QDate getTakenDate() const;
    float getWeight() const;
    float getShoulder() const;
    float getChest() const;
    float getArm() const;
    float getBelly() const;
    float getHip() const;
    float getLeg() const;

    void setWeight(float weight);
    void setShoulder(float shoulder);
    void setChest(float chest);
    void setArm(float arm);
    void setBelly(float belly);
    void setHip(float hip);
    void setLeg(float leg);

private:
    QDate taken_date_{QDate::currentDate()};
    float weight_;
    float shoulder_;
    float chest_;
    float arm_;
    float belly_;
    float hip_;
    float leg_;
};

#endif // MEASUREMENT_H
