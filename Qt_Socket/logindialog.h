#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H
#include <QTimer>
#include <QDate>
#include <QTime>
#include <QDialog>

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = 0);
    ~LoginDialog();

private slots:
    void on_btnExit_clicked();

    void on_btnLogin_clicked();
    void qtimeSlot();

private:
    Ui::LoginDialog *ui;
    QTimer *timer;
};

#endif // LOGINDIALOG_H
