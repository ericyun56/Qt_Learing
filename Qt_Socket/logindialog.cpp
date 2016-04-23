#include "logindialog.h"
#include "ui_logindialog.h"
#include <QDebug>
#include <QString>
#include <QFile>
#include <QSettings>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QStringList>
LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);

    this->setWindowTitle("欢迎登录");

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(qtimeSlot()));
    timer->start(1000);

    QFile f1(QCoreApplication::applicationDirPath()+QString("/Option.ini"));

    if(f1.size())
    {
        QSettings settings(QCoreApplication::applicationDirPath()+QString("/Option.ini"), QSettings::IniFormat);

        QString username = settings.value("DevOption/username").toString();
        QString passwd = settings.value("DevOption/passwd").toString();


        ui->editUserName->setText(username);
        ui->editPasswd->setText(passwd);
    }

}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::qtimeSlot()
{
    QTime qtimeObj = QTime::currentTime();

    QString strTime = qtimeObj.toString("hh:mm:ss");
    strTime.prepend("时间:");
    QDate qdateObj = QDate::currentDate();
    QString strDate = qdateObj.toString("yyyy年M月d日 dddd  "); //星期、月份、天、年
    strDate.prepend("今天是:");

    strDate.append(strTime);
    ui->timeLabel->setText (strDate);

    //qDebug() << strTime;
    //qDebug() << strDate;


}

void LoginDialog::on_btnExit_clicked()
{
    this->close();
}

void LoginDialog::on_btnLogin_clicked()
{
    QString mUserName;
    QString mPasswd;

    mUserName = ui->editUserName->text();
    mPasswd = ui->editPasswd->text();


    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("ArchivesManagementSystem");
    db.setUserName("root");
    db.setPassword("ma2015");
    if (!db.open())
        qDebug() << "Failed to connect to root mysql admin";

    QSqlQuery query(db);
    query.exec("select userLoginName,userPasswd from admin_user");
    QString value0;
    QString value1;

    if(ui->radRemember->isChecked())
    {

        while(query.next())
        {

            value0 = query.value(0).toString();
            value1 = query.value(1).toString();
            if((mUserName== value0)&&(mPasswd==value1))
            {
                QSettings settings(QCoreApplication::applicationDirPath()+QString("/infor.ini"), QSettings::IniFormat); // 当前目录的INI文件
                settings.beginGroup("DevOption");

                settings.setValue("username", mUserName);
                settings.setValue("passwd", mPasswd);

                settings.endGroup();

                accept();
            }

        }


        if(mUserName.isEmpty() || mPasswd.isEmpty())
        {
            QMessageBox::warning(this,tr("Warning"),("用户名或密码为空"),QMessageBox::Yes);    //警告对话框
            ui->editUserName->clear();                      //清除用户名
            ui->editPasswd->clear();
            ui->editUserName->setFocus();
        }

    }

    else if(!ui->radRemember->isChecked())
    {
        if(mUserName.isEmpty() || mPasswd.isEmpty())
        {
            QMessageBox::warning(this,tr("Warning"),("用户名或密码为空"),QMessageBox::Yes);    //警告对话框
             ui->editUserName->setFocus();
        }

        else if(mUserName==tr("admin")&&mPasswd==tr("admin"))
        {
            accept();
        }
    }

    else if(mUserName.isEmpty() || mPasswd.isEmpty())
    {
        QMessageBox::warning(this,tr("Warning"),("用户名或密码为空"),QMessageBox::Yes);    //警告对话框
         ui->editUserName->setFocus();
    }
    else
    {


          QMessageBox::warning(this,tr("Warning"),("用户名或密码错误! 请重新输入"),QMessageBox::Yes);    //警告对话框
          ui->editUserName->clear();                      //清除用户名
          ui->editPasswd->clear();                 //清除密码
          ui->editUserName->setFocus();              //鼠标回到用户名栏
    }
}
