#ifndef RECONNECTDIALOG_H
#define RECONNECTDIALOG_H

#include <QDialog>

namespace Ui {
class ReconnectDialog;
}

class ReconnectDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ReconnectDialog(const QString &message, QWidget *parent = nullptr);
    ~ReconnectDialog();

signals:
    void Reconnect(const QString &password);

private slots:
    void OnReconnectButtonClicked();

private:
    Ui::ReconnectDialog *ui;
};

#endif // RECONNECTDIALOG_H
