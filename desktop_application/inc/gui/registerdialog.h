#ifndef REGISTERDIALOG_H
#define REGISTERDIALOG_H

#include <QDialog>
#include <memory>
#include "../../inc/member/member.h"

enum RegisterScreen{
    InfoPage,
    SubscriptionPage,
    PaymentPage
};

namespace Ui {
class RegisterDialog;
}

class RegisterDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RegisterDialog(QWidget *parent = nullptr);
    ~RegisterDialog();

signals:
    void MemberCreated(const std::unique_ptr<Member> &new_member);

private slots:
    void OnNextButtonInfoClicked();
    void OnNextButtonSubClicked();
    void OnSaveButtonClicked();

private:
    Ui::RegisterDialog *ui;
    std::unique_ptr<Member> new_member_;
};

#endif // REGISTERDIALOG_H
