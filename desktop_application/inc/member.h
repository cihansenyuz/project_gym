#ifndef MEMBER_H
#define MEMBER_H

#include <QString>
#include <QDate>

class Member
{
public:
    Member(const QString &name, int age, float weight);
    void SetSubscriptionStartDate(const QDate &start_date, const QDate &end_date);
    void SetSubscriptionEndDate(const QDate &start_date, const QDate &end_date);
    void SetWeight(float weight);

private:
    QString name_;
    int age_;
    float weight_;
    bool subscription_{false};
    QDate start_date_;
    QDate end_date_;
};

#endif // MEMBER_H
