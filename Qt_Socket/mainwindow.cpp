#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDesktopWidget>
#include <QRect>
#include <QDebug>
#include <QPalette>
#include <QListWidget>
#include <QListWidgetItem>
#include <QMessageBox>
#include <QModelIndex>
#include <QTableWidgetItem>
#include <QFont>
#include <QDialog>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("干部档案管理系统");

    QDesktopWidget* desktopWidget = QApplication::desktop();
    QRect screenRect = desktopWidget->screenGeometry();
    int g_nActScreenW = screenRect.width();
    int g_nActScreenH = screenRect.height();
    this->setGeometry(130,50,g_nActScreenW-300,g_nActScreenH-200);


    this->setAutoFillBackground(true);
    QPalette palette;
    palette.setColor(QPalette::Background, QColor(205, 230, 199));
    //palette.setBrush(QPalette::Background, QBrush(QPixmap(":/background.png")));
    this->setPalette(palette);

    timer_2 = new QTimer(this);
    connect(timer_2, SIGNAL(timeout()), this, SLOT(qtimeSlot_2()));
    timer_2->start(1000);

    ui->stackedWidget->setCurrentIndex(0);
    ui->labLoginName->setText("当前正在登录的用户：Administrator");
    ui->tabShowInformation->setRowCount(50);
    ui->tabShowInformation->setColumnCount(9);
    ui->tabShowInformation->setColumnWidth(1,120);
    ui->tabShowInformation->setColumnWidth(3,150);

    ui->tabDisplayDel->setRowCount(50);
    ui->tabDisplayDel->setColumnCount(9);
    //ui->tabDisplayDel->setColumnWidth(1,120);
    //ui->tabDisplayDel->setColumnWidth(3,150);



    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("ArchivesManagementSystem");
    db.setUserName("root");
    db.setPassword("ma2015");
    if (!db.open())
        //  qDebug() << "Failed to connect to root mysql admin";
        QMessageBox::warning(this,tr("警告"),("请确认数据库服务是否启动"),QMessageBox::Yes);
    else
    {
        QMessageBox::information(this,tr("信息"),("数据库已启动"),QMessageBox::Yes);
    }

    QSqlQuery query(db);

    query.exec("select username from baseinfor");
    while(query.next())
    {

        QString value0 = query.value(0).toString();
        ui->listIndex->insertItem(0, value0);
        ui->listIndexDel->insertItem(0, value0);
    }

    query.exec("select * from baseinfor");
    int rowNumber = 0,columnNumber = 0;
    while(query.next())
    {
        QString insertValue0,insertValue1,insertValue2;
        QString insertValue3,insertValue4;
        QString insertValue5,insertValue6;
        QString insertValue7;
        QString insertValue8;

        insertValue0 = query.value(0).toString();
        insertValue1 = query.value(1).toString();
        insertValue2 = query.value(2).toString();
        insertValue3 = query.value(3).toString();
        insertValue4 = query.value(4).toString();
        insertValue5 = query.value(5).toString();
        insertValue6 = query.value(6).toString();
        insertValue7 = query.value(7).toString();
        insertValue8 = query.value(8).toString();

        ui->tabShowInformation->setItem(rowNumber,columnNumber,new QTableWidgetItem(insertValue0));
        ui->tabShowInformation->setItem(rowNumber,columnNumber+1,new QTableWidgetItem(insertValue1));
        ui->tabShowInformation->setItem(rowNumber,columnNumber+2,new QTableWidgetItem(insertValue2));
        ui->tabShowInformation->setItem(rowNumber,columnNumber+3,new QTableWidgetItem(insertValue3));
        ui->tabShowInformation->setItem(rowNumber,columnNumber+4,new QTableWidgetItem(insertValue4));
        ui->tabShowInformation->setItem(rowNumber,columnNumber+5,new QTableWidgetItem(insertValue5));
        ui->tabShowInformation->setItem(rowNumber,columnNumber+6,new QTableWidgetItem(insertValue6));
        ui->tabShowInformation->setItem(rowNumber,columnNumber+7,new QTableWidgetItem(insertValue7));
        ui->tabShowInformation->setItem(rowNumber,columnNumber+8,new QTableWidgetItem(insertValue8));



        ui->tabDisplayDel->setItem(rowNumber,columnNumber,new QTableWidgetItem(insertValue0));
        ui->tabDisplayDel->setItem(rowNumber,columnNumber+1,new QTableWidgetItem(insertValue1));
        ui->tabDisplayDel->setItem(rowNumber,columnNumber+2,new QTableWidgetItem(insertValue2));
        ui->tabDisplayDel->setItem(rowNumber,columnNumber+3,new QTableWidgetItem(insertValue3));
        ui->tabDisplayDel->setItem(rowNumber,columnNumber+4,new QTableWidgetItem(insertValue4));
        ui->tabDisplayDel->setItem(rowNumber,columnNumber+5,new QTableWidgetItem(insertValue5));
        ui->tabDisplayDel->setItem(rowNumber,columnNumber+6,new QTableWidgetItem(insertValue6));
        ui->tabDisplayDel->setItem(rowNumber,columnNumber+7,new QTableWidgetItem(insertValue7));
        ui->tabDisplayDel->setItem(rowNumber,columnNumber+8,new QTableWidgetItem(insertValue8));


        rowNumber++;
    }
    db.close();

    ui->commandFinish->hide();
    calender = new QCalendarWidget(this);
    this->calender->setGeometry(120,350,270,230);
    this->calender->setDateEditEnabled(true);
    //calender->resize(250,230);
    this->calender->hide();

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::qtimeSlot_2()
{
    QTime qtimeObj = QTime::currentTime();

    QString strTime = qtimeObj.toString("hh:mm:ss");
    strTime.prepend("时间:");
    QDate qdateObj = QDate::currentDate();
    QString strDate = qdateObj.toString("yyyy年M月d日 dddd  "); //星期、月份、天、年
    strDate.prepend("今天是:");

    strDate.append(strTime);
    ui->labTime->setText(strDate);
}

bool MainWindow::getIDFromDB()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("ArchivesManagementSystem");
    db.setUserName("root");
    db.setPassword("ma2015");
    if (!db.open())
        qDebug() << "Failed to connect to root mysql admin";
    //else qDebug() << "open";

    QSqlQuery query(db);

    query.exec("select userID from baseinfor");
    ui->listIndex->clear();
    while(query.next())
    {

        QString value0 = query.value(0).toString();

        ui->listIndex->insertItem(0, value0);
    }

    db.close();

    return 0;
}


bool MainWindow::getIDFromDB_Del()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("ArchivesManagementSystem");
    db.setUserName("root");
    db.setPassword("ma2015");
    if (!db.open())
        qDebug() << "Failed to connect to root mysql admin";
    //else qDebug() << "open";

    QSqlQuery query(db);

    query.exec("select userID from baseinfor");
    ui->listIndexDel->clear();
    while(query.next())
    {

        QString value0 = query.value(0).toString();

        ui->listIndexDel->insertItem(0, value0);
    }

    db.close();

    return 0;
}


bool MainWindow::getDepartmentFromDB()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("ArchivesManagementSystem");
    db.setUserName("root");
    db.setPassword("ma2015");
    if (!db.open())
        qDebug() << "Failed to connect to root mysql admin";
    //else qDebug() << "open";

    QSqlQuery query(db);

    query.exec("select distinct department from baseinfor");
    ui->listIndex->clear();
    while(query.next())
    {

        QString value0 = query.value(0).toString();
        ui->listIndex->insertItem(0, value0);

        // qDebug() << value0 ;
    }

    db.close();
    return 0;
}


bool MainWindow::getDepartmentFromDB_Del()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("ArchivesManagementSystem");
    db.setUserName("root");
    db.setPassword("ma2015");
    if (!db.open())
        qDebug() << "Failed to connect to root mysql admin";
    //else qDebug() << "open";

    QSqlQuery query(db);

    query.exec("select distinct department from baseinfor");
    ui->listIndexDel->clear();
    while(query.next())
    {

        QString value0 = query.value(0).toString();
        ui->listIndexDel->insertItem(0, value0);

        // qDebug() << value0 ;
    }

    db.close();
    return 0;
}


bool MainWindow::getNameFromDB()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("ArchivesManagementSystem");
    db.setUserName("root");
    db.setPassword("ma2015");
    if (!db.open())
        qDebug() << "Failed to connect to root mysql admin";
    // else qDebug() << "open";

    QSqlQuery query(db);

    query.exec("select username from baseinfor");
    ui->listIndex->clear();
    while(query.next())
    {

        QString value0 = query.value(0).toString();
        ui->listIndex->insertItem(0, value0);

        //qDebug() << value0 ;
    }

    db.close();
    return 0;
}


bool MainWindow::getNameFromDB_Del()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("ArchivesManagementSystem");
    db.setUserName("root");
    db.setPassword("ma2015");
    if (!db.open())
        qDebug() << "Failed to connect to root mysql admin";
    // else qDebug() << "open";

    QSqlQuery query(db);

    query.exec("select username from baseinfor");
    ui->listIndexDel->clear();
    while(query.next())
    {

        QString value0 = query.value(0).toString();
        ui->listIndexDel->insertItem(0, value0);

        //qDebug() << value0 ;
    }

    db.close();
    return 0;
}



void MainWindow::on_comIndex_currentIndexChanged(int index)
{
    if(index == 0)
    {
        getNameFromDB();
    }

    else if(index == 1)
    {
        getIDFromDB();
    }

    else if(index == 2)
    {
        getDepartmentFromDB();
    }

}


void MainWindow::on_btnSearch_clicked()
{

    // int index = ui->comIndex->currentIndex();
    // qDebug() << index;

    QString searchIndex = ui->editIndex->text();
    QString list;

    if(searchIndex.isEmpty())
    {
        QMessageBox::information(this,tr("警告"),("请输入"),QMessageBox::Yes);
    }
    else
    {
        for(int i =0 ;i < (ui->listIndex->count());i++)
        {
            ui->listIndex->setCurrentRow(i);
            list = ui->listIndex->currentItem()->text();
            if(searchIndex == list)
            {
                ui->listIndex->clear();
                ui->listIndex->insertItem(0, searchIndex);
            }
            else if(i == (ui->listIndex->count()) - 1)
            {
                //ui->listIndex->clear();
                QMessageBox::information(this,tr("警告"),("没有发现"),QMessageBox::Yes);

            }
        }
    }
}


void MainWindow::on_editIndex_editingFinished()
{
    QString searchIndex = ui->editIndex->text();

    QString list;
    for(int i =0 ;i < (ui->listIndex->count());i++)
    {
        ui->listIndex->setCurrentRow(i);
        list = ui->listIndex->currentItem()->text();
        if(searchIndex == list)
        {
            ui->listIndex->clear();
            ui->listIndex->insertItem(0, searchIndex);

        }
        else if(i == (ui->listIndex->count()) - 1)
        {
            // ui->listIndex->clear();
            QMessageBox::information(this,tr("警告"),("没有发现"),QMessageBox::Yes);
        }
    }
}


void MainWindow::on_listIndex_itemClicked(QListWidgetItem *item)
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("ArchivesManagementSystem");
    db.setUserName("root");
    db.setPassword("ma2015");
    if (!db.open())
        qDebug() << "Failed to connect to root mysql admin";

    QSqlQuery query(db);

    //qDebug() << item->text();
    int index = ui->comIndex->currentIndex();
    QString itm = ui->listIndex->currentItem()->text();
    //item->setBackgroundColor(QColor(255, 85, 0));


    if(index == 0)
    {
        itm.remove("name");
        itm.prepend("\'");
        itm.prepend( "select * from baseinfor where username=");
        itm.append("\'");
        query.exec( itm);
    }
    else if(index == 1)
    {
        itm.remove("name");
        itm.prepend("\'");
        itm.prepend( "select * from baseinfor where userID=");
        itm.append("\'");
        query.exec( itm);
    }

    else if(index == 2)
    {
        itm.remove("name");
        itm.prepend("\'");
        itm.prepend( "select * from baseinfor where department=");
        itm.append("\'");
        query.exec( itm);
    }

    ui->tabShowInformation->clear();
    //QFont font  = ui->tabShowInformation->horizontalHeader()->font();
    // font.setPointSize(36);
    ui->tabShowInformation->setHorizontalHeaderItem(0,new QTableWidgetItem("姓名"));
    ui->tabShowInformation->setHorizontalHeaderItem(1,new QTableWidgetItem("工号"));
    ui->tabShowInformation->setHorizontalHeaderItem(2,new QTableWidgetItem("性别"));
    ui->tabShowInformation->setHorizontalHeaderItem(3,new QTableWidgetItem("名族"));
    ui->tabShowInformation->setHorizontalHeaderItem(4,new QTableWidgetItem("籍贯"));
    ui->tabShowInformation->setHorizontalHeaderItem(5,new QTableWidgetItem("出生日期"));
    ui->tabShowInformation->setHorizontalHeaderItem(6,new QTableWidgetItem("政治面貌"));
    ui->tabShowInformation->setHorizontalHeaderItem(7,new QTableWidgetItem("学历"));
    ui->tabShowInformation->setHorizontalHeaderItem(8,new QTableWidgetItem("部门"));

    int rowNumber = 0,columnNumber = 0;
    while(query.next())
    {

        QString insertValue0,insertValue1,insertValue2;
        QString insertValue3,insertValue4;
        QString insertValue5,insertValue6;
        QString insertValue7;
        QString insertValue8;


        insertValue0 = query.value(0).toString();
        insertValue1 = query.value(1).toString();
        insertValue2 = query.value(2).toString();
        insertValue3 = query.value(3).toString();
        insertValue4 = query.value(4).toString();
        insertValue5 = query.value(5).toString();
        insertValue6 = query.value(6).toString();
        insertValue7 = query.value(7).toString();
        insertValue8 = query.value(8).toString();


        ui->tabShowInformation->setItem(rowNumber,columnNumber,new QTableWidgetItem(insertValue0));
        ui->tabShowInformation->setItem(rowNumber,columnNumber+1,new QTableWidgetItem(insertValue1));
        ui->tabShowInformation->setItem(rowNumber,columnNumber+2,new QTableWidgetItem(insertValue2));
        ui->tabShowInformation->setItem(rowNumber,columnNumber+3,new QTableWidgetItem(insertValue3));
        ui->tabShowInformation->setItem(rowNumber,columnNumber+4,new QTableWidgetItem(insertValue4));
        ui->tabShowInformation->setItem(rowNumber,columnNumber+5,new QTableWidgetItem(insertValue5));
        ui->tabShowInformation->setItem(rowNumber,columnNumber+6,new QTableWidgetItem(insertValue6));
        ui->tabShowInformation->setItem(rowNumber,columnNumber+7,new QTableWidgetItem(insertValue7));
        ui->tabShowInformation->setItem(rowNumber,columnNumber+8,new QTableWidgetItem(insertValue8));


        rowNumber++;

    }
    db.close();
}

void MainWindow::on_btnPageAdd_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}


//退出删除
void MainWindow::on_btnPageDel_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);



    //    bool focus = tableWidget->isItemSelected(tableWidget->currentItem()); // 判断是否选中一行

    //      Int row1 = tableWidget->currentItem()->row(); // 当前选中行

}

void MainWindow::on_btnAdd_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_btnDel_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
    ui->listIndexDel->clear();

    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("ArchivesManagementSystem");
    db.setUserName("root");
    db.setPassword("ma2015");
    if (!db.open())
        //  qDebug() << "Failed to connect to root mysql admin";
        QMessageBox::warning(this,tr("警告"),("请确认数据库服务是否启动"),QMessageBox::Yes);


    QSqlQuery query(db);

    query.exec("select username from baseinfor");
    while(query.next())
    {

        QString value0 = query.value(0).toString();

        ui->listIndexDel->insertItem(0, value0);
    }

    query.exec("select * from baseinfor");
    int rowNumber = 0,columnNumber = 0;
    while(query.next())
    {
        QString insertValue0,insertValue1,insertValue2;
        QString insertValue3,insertValue4;
        QString insertValue5,insertValue6;
        QString insertValue7;
        QString insertValue8;

        insertValue0 = query.value(0).toString();
        insertValue1 = query.value(1).toString();
        insertValue2 = query.value(2).toString();
        insertValue3 = query.value(3).toString();
        insertValue4 = query.value(4).toString();
        insertValue5 = query.value(5).toString();
        insertValue6 = query.value(6).toString();
        insertValue7 = query.value(7).toString();
        insertValue8 = query.value(8).toString();


        ui->tabDisplayDel->setItem(rowNumber,columnNumber,new QTableWidgetItem(insertValue0));
        ui->tabDisplayDel->setItem(rowNumber,columnNumber+1,new QTableWidgetItem(insertValue1));
        ui->tabDisplayDel->setItem(rowNumber,columnNumber+2,new QTableWidgetItem(insertValue2));
        ui->tabDisplayDel->setItem(rowNumber,columnNumber+3,new QTableWidgetItem(insertValue3));
        ui->tabDisplayDel->setItem(rowNumber,columnNumber+4,new QTableWidgetItem(insertValue4));
        ui->tabDisplayDel->setItem(rowNumber,columnNumber+5,new QTableWidgetItem(insertValue5));
        ui->tabDisplayDel->setItem(rowNumber,columnNumber+6,new QTableWidgetItem(insertValue6));
        ui->tabDisplayDel->setItem(rowNumber,columnNumber+7,new QTableWidgetItem(insertValue7));
        ui->tabDisplayDel->setItem(rowNumber,columnNumber+8,new QTableWidgetItem(insertValue8));


        rowNumber++;
    }
    db.close();



}

void MainWindow::on_commandChoose_clicked()
{

    //qDebug() <<　this->calender->geometry();
    this->calender->show();
    ui->editCalender->clear();
    ui->commandChoose->hide();
    ui->commandFinish->show();
}

void MainWindow::on_commandFinish_clicked()
{
    this->calender->hide();
    ui->commandFinish->hide();
    ui->commandChoose->show();
    ui->editCalender->clear();

    QString cal =  this->calender->selectedDate().toString("yyyy-MM-dd");
    QString calAge =  this->calender->selectedDate().toString("yyyy");
    int age = calAge.toInt();
    age= 2016 - age;
    qDebug() << age;

    ui->editCalender->setText("  " + cal);
    ui->editAge->setText(QString::number(age));


}

void MainWindow::on_pushButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);


}

void MainWindow::on_btnDetail_clicked()
{

    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("ArchivesManagementSystem");
    db.setUserName("root");
    db.setPassword("ma2015");
    if (!db.open())
        //  qDebug() << "Failed to connect to root mysql admin";
        QMessageBox::warning(this,tr("警告"),("请确认数据库服务是否启动"),QMessageBox::Yes);

    QSqlQuery query(db);


    query.exec("select * from privateinfor");
    int rowNumber = 0,columnNumber = 0;
    while(query.next())
    {
        ui->tabDatail->setRowCount(50);
        ui->tabDatail->setColumnCount(7);

        ui->tabDatail->setColumnWidth(1,150);
        ui->tabDatail->setColumnWidth(3,240);



        qDebug() << "Cross";

        QString insertValue0,insertValue1,insertValue2;
        QString insertValue3,insertValue4;
        QString insertValue5;
//        QString insertValue5,insertValue6;
//        QString insertValue7;
//        QString insertValue8;

        insertValue0 = query.value(0).toString();
        insertValue1 = query.value(1).toString();
        insertValue2 = query.value(2).toString();
        insertValue3 = query.value(3).toString();
        insertValue4 = query.value(4).toString();
        insertValue5 = query.value(5).toString();
//        insertValue6 = query.value(6).toString();
//        insertValue7 = query.value(7).toString();
//        insertValue8 = query.value(8).toString();

        ui->tabDatail->setItem(rowNumber,columnNumber,new QTableWidgetItem(insertValue0));
        ui->tabDatail->setItem(rowNumber,columnNumber+1,new QTableWidgetItem(insertValue1));
        ui->tabDatail->setItem(rowNumber,columnNumber+2,new QTableWidgetItem(insertValue2));
        ui->tabDatail->setItem(rowNumber,columnNumber+3,new QTableWidgetItem(insertValue3));
        ui->tabDatail->setItem(rowNumber,columnNumber+4,new QTableWidgetItem(insertValue4));

        ui->tabDatail->setItem(rowNumber,columnNumber+5,new QTableWidgetItem(insertValue5));


        rowNumber++;
    }
    db.close();



    ui->stackedWidget->setCurrentIndex(3);
}

void MainWindow::on_btnAddToDataBase_clicked()
{
    QString insertUsername;
    QString insertUserID;
    QString insertUserGender;
    QString insertUserNation;
    QString insertUserPlace;
    QString insertUserBirth;
    QString insertUserPolitical;
    QString insertUserDegree;
    QString insertUserDepartment;

    QString insertUserSalary;
    QString insertUserCardId;
    QString insertUserAge;
    QString insertUserPosition;

    insertUsername = ui->editname->text();
    insertUserID = ui->editID->text();
    insertUserNation = ui->editNation->text();
    insertUserPlace = ui->editPlace->text();
    insertUserBirth = this->calender->selectedDate().toString("yyyy-MM-dd");
    insertUserPolitical = ui->editPolitical->text();
    insertUserDegree = ui->editDegree->text();
    insertUserDepartment = ui->editDepartment->text();
    insertUserSalary = ui->editSalary->text();
    insertUserCardId = ui->editCardID->text();
    insertUserAge = ui->editAge->text();
    insertUserPosition = ui->editPosition->text();






    while(insertUsername.isEmpty())
    {
        QMessageBox::warning(this,tr("警告"),("请输入姓名"),QMessageBox::Yes);
        ui->editname->setFocus();
        break;
    }
    while(insertUserID.isEmpty())
    {
        QMessageBox::warning(this,tr("警告"),("请输入ID"),QMessageBox::Yes);
        ui->editID->setFocus();
        break;
    }
    while(insertUserNation.isEmpty())
    {
        QMessageBox::warning(this,tr("警告"),("请输入民族"),QMessageBox::Yes);
        ui->editNation->setFocus();
        break;
    }
    while(insertUserPlace.isEmpty())
    {
        QMessageBox::warning(this,tr("警告"),("请输入籍贯"),QMessageBox::Yes);
        ui->editPlace->setFocus();
        break;
    }
    while(insertUserPolitical.isEmpty())
    {
        QMessageBox::warning(this,tr("警告"),("请输入政治面貌"),QMessageBox::Yes);
        ui->editPolitical->setFocus();
        break;
    }
    while(insertUserDegree.isEmpty())
    {
        QMessageBox::warning(this,tr("警告"),("请输入学历"),QMessageBox::Yes);
        ui->editDegree->setFocus();
        break;
    }

    while(insertUserDepartment.isEmpty())
    {
        QMessageBox::warning(this,tr("警告"),("请输入部门名称"),QMessageBox::Yes);
        ui->editDepartment->setFocus();
        break;
    }

    while(ui->editCalender->text().isEmpty())
    {
        QMessageBox::warning(this,tr("警告"),("请选择出生日期"),QMessageBox::Yes);
        ui->editname->setFocus();
        break;
    }

    if(ui->radMale->isChecked())
    {
        insertUserGender = "男";
    }

    if(ui->radFemale->isChecked())
    {
        insertUserGender = "女";
    }

    //    qDebug() << insertUsername;
    //    qDebug() << insertUserID;
    //    qDebug() << insertUserNation;
    //    qDebug() << insertUserPlace;
    //    qDebug() << insertUserBirth;
    //    qDebug() << insertUserPolitical;
    //    qDebug() << insertUserDegree;
    //    qDebug() << insertUserDepartment;
    //    qDebug() << insertUserGender;


    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("ArchivesManagementSystem");
    db.setUserName("root");
    db.setPassword("ma2015");
    if (!db.open())
        qDebug() << "Failed to connect to root mysql admin";

    QSqlQuery query(db);

    query.prepare("insert into baseinfor(username,userID,gender,nation,nativePlace,birth,politicalStatus,degree,department)"
                  "values(:username,:userID,:gender,:nation,:nativePlace,:birth,:politicalStatus,:degree,:department)");
    query.bindValue(":username",insertUsername);
    query.bindValue(":userID",insertUserID);
    query.bindValue(":gender",insertUserGender);
    query.bindValue(":nation",insertUserNation);
    query.bindValue(":nativePlace",insertUserPlace);
    query.bindValue(":birth",insertUserBirth);
    query.bindValue(":politicalStatus",insertUserPolitical);
    query.bindValue(":degree",insertUserDegree);
    query.bindValue(":department",insertUserDepartment);

    bool isAllWriting = !(insertUsername.isEmpty()) && !(insertUserID.isEmpty()) && !(insertUserBirth.isEmpty()) && !(insertUserDepartment.isEmpty());
    if(isAllWriting)
    {
        if(query.exec())
        {
            //QMessageBox::information(this,tr("通知"),("添加成功"),QMessageBox::Yes);
           // ui->stackedWidget->setCurrentIndex(0);
            ui->editname->clear();
            ui->editID->clear();
            ui->editNation->clear();
            ui->editPlace->clear();
            ui->editCalender->clear();
            ui->editPolitical->clear();
            ui->editDegree->clear();
            ui->editDepartment->clear();

        }


        query.prepare("insert into privateinfor(username,userID,salary,cardID,age,position)"
                      "values(:username,:userID,:salary,:cardID,:age,:position)");
        query.bindValue(":username",insertUsername);
        query.bindValue(":userID",insertUserID);
        query.bindValue(":salary",insertUserSalary);
        query.bindValue(":cardID",insertUserCardId);
        query.bindValue(":age",insertUserAge);
        query.bindValue(":position",insertUserPosition);

        if(query.exec())
        {
            QMessageBox::information(this,tr("通知"),("添加成功"),QMessageBox::Yes);
            ui->stackedWidget->setCurrentIndex(0);


            ui->editSalary->clear();
            ui->editCardID->clear();
            ui->editAge->clear();
            ui->editPosition->clear();

        }


    }


    db.close();

}

void MainWindow::on_btnReset_clicked()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("ArchivesManagementSystem");
    db.setUserName("root");
    db.setPassword("ma2015");
    if (!db.open())
        //  qDebug() << "Failed to connect to root mysql admin";
        QMessageBox::warning(this,tr("警告"),("请确认数据库服务是否启动"),QMessageBox::Yes);

    QSqlQuery query(db);

    query.exec("select username from baseinfor");
    while(query.next())
    {

        QString value0 = query.value(0).toString();
        ui->listIndex->insertItem(0, value0);
    }

    query.exec("select * from baseinfor");
    int rowNumber = 0,columnNumber = 0;
    while(query.next())
    {
        QString insertValue0,insertValue1,insertValue2;
        QString insertValue3,insertValue4;
        QString insertValue5,insertValue6;
        QString insertValue7,insertValue8;

        insertValue0 = query.value(0).toString();
        insertValue1 = query.value(1).toString();
        insertValue2 = query.value(2).toString();
        insertValue3 = query.value(3).toString();
        insertValue4 = query.value(4).toString();
        insertValue5 = query.value(5).toString();
        insertValue6 = query.value(6).toString();
        insertValue7= query.value(7).toString();
        insertValue8= query.value(8).toString();


        ui->tabShowInformation->setItem(rowNumber,columnNumber,new QTableWidgetItem(insertValue0));
        ui->tabShowInformation->setItem(rowNumber,columnNumber+1,new QTableWidgetItem(insertValue1));
        ui->tabShowInformation->setItem(rowNumber,columnNumber+2,new QTableWidgetItem(insertValue2));
        ui->tabShowInformation->setItem(rowNumber,columnNumber+3,new QTableWidgetItem(insertValue3));
        ui->tabShowInformation->setItem(rowNumber,columnNumber+4,new QTableWidgetItem(insertValue4));
        ui->tabShowInformation->setItem(rowNumber,columnNumber+5,new QTableWidgetItem(insertValue5));
        ui->tabShowInformation->setItem(rowNumber,columnNumber+6,new QTableWidgetItem(insertValue6));
        ui->tabShowInformation->setItem(rowNumber,columnNumber+7,new QTableWidgetItem(insertValue7));
        ui->tabShowInformation->setItem(rowNumber,columnNumber+8,new QTableWidgetItem(insertValue8));


        rowNumber++;
    }
    db.close();
}

void MainWindow::on_pushButton_2_clicked()
{

    //QMessageBox::information(this,tr("通知"),("添加成功"),QMessageBox::Yes || QMessageBox::No);

    QMessageBox msgBox;
    // msgBox.setText("The document has been modified.");
    msgBox.setInformativeText("你想放弃添加？");
    msgBox.setStandardButtons(QMessageBox::Discard | QMessageBox::Cancel);
    // msgBox.setDefaultButton(QMessageBox::Save);
    int ret = msgBox.exec();

    switch (ret) {
    case QMessageBox::Discard:
        ui->stackedWidget->setCurrentIndex(0);
        ui->editname->clear();
        ui->editID->clear();
        ui->editCalender->clear();
        ui->editDepartment->clear();
        ui->editPolitical->clear();
        ui->editPlace->clear();
        ui->editNation->clear();
        ui->editDegree->clear();
        break;
    case QMessageBox::Cancel:
        ui->editname->setFocus();
        // Cancel was clicked
        break;
    default:
        // should never be reached
        break;
    }



}

void MainWindow::on_btnPageDelVerify_clicked()
{
    QString searchIndex = ui->editIndexDel->text();
    QString list;

    if(searchIndex.isEmpty())
    {
        QMessageBox::information(this,tr("警告"),("请输入"),QMessageBox::Yes);
    }
    else
    {
        for(int i =0 ;i < (ui->listIndexDel->count());i++)
        {
            ui->listIndexDel->setCurrentRow(i);
            list = ui->listIndexDel->currentItem()->text();
            if(searchIndex == list)
            {
                ui->listIndexDel->clear();
                ui->listIndexDel->insertItem(0, searchIndex);
            }
            else if(i == (ui->listIndexDel->count()) - 1)
            {
                //ui->listIndex->clear();
                QMessageBox::information(this,tr("警告"),("没有发现"),QMessageBox::Yes);

            }
        }
    }
}

void MainWindow::on_comIndexDel_currentIndexChanged(int index)
{
    if(index == 0)
    {
        getNameFromDB_Del();
    }

    else if(index == 1)
    {
        getIDFromDB_Del();
    }

    else if(index == 2)
    {
        getDepartmentFromDB_Del();
    }
}

void MainWindow::on_listIndexDel_clicked(const QModelIndex &Oindex)
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("ArchivesManagementSystem");
    db.setUserName("root");
    db.setPassword("ma2015");
    if (!db.open())
        qDebug() << "Failed to connect to root mysql admin";

    QSqlQuery query(db);

    //qDebug() << item->text();
    int index = ui->comIndexDel->currentIndex();
    QString itm = ui->listIndexDel->currentItem()->text();
    //item->setBackgroundColor(QColor(255, 85, 0));


    if(index == 0)
    {
        itm.remove("name");
        itm.prepend("\'");
        itm.prepend( "select * from baseinfor where username=");
        itm.append("\'");
        query.exec( itm);
    }
    else if(index == 1)
    {
        itm.remove("name");
        itm.prepend("\'");
        itm.prepend( "select * from baseinfor where userID=");
        itm.append("\'");
        query.exec( itm);
    }

    else if(index == 2)
    {
        itm.remove("name");
        itm.prepend("\'");
        itm.prepend( "select * from baseinfor where department=");
        itm.append("\'");
        query.exec( itm);
    }

    ui->tabDisplayDel->clear();
    //QFont font  = ui->tabShowInformation->horizontalHeader()->font();
    // font.setPointSize(36);

    ui->tabDisplayDel->setHorizontalHeaderItem(0,new QTableWidgetItem("姓名"));
    ui->tabDisplayDel->setHorizontalHeaderItem(1,new QTableWidgetItem("工号"));
    ui->tabDisplayDel->setHorizontalHeaderItem(2,new QTableWidgetItem("性别"));
    ui->tabDisplayDel->setHorizontalHeaderItem(3,new QTableWidgetItem("名族"));
    ui->tabDisplayDel->setHorizontalHeaderItem(4,new QTableWidgetItem("籍贯"));
    ui->tabDisplayDel->setHorizontalHeaderItem(5,new QTableWidgetItem("出生日期"));
    ui->tabDisplayDel->setHorizontalHeaderItem(6,new QTableWidgetItem("政治面貌"));
    ui->tabDisplayDel->setHorizontalHeaderItem(7,new QTableWidgetItem("学历"));
    ui->tabDisplayDel->setHorizontalHeaderItem(8,new QTableWidgetItem("部门"));

    int rowNumber = 0,columnNumber = 0;
    while(query.next())
    {

        QString insertValue0,insertValue1,insertValue2;
        QString insertValue3,insertValue4;
        QString insertValue5,insertValue6;
        QString insertValue7,insertValue8;

        insertValue0 = query.value(0).toString();
        insertValue1 = query.value(1).toString();
        insertValue2 = query.value(2).toString();
        insertValue3 = query.value(3).toString();
        insertValue4 = query.value(4).toString();
        insertValue5 = query.value(2).toString();
        insertValue6 = query.value(3).toString();
        insertValue7= query.value(4).toString();
        insertValue8= query.value(4).toString();


        ui->tabDisplayDel->setItem(rowNumber,columnNumber,new QTableWidgetItem(insertValue0));
        ui->tabDisplayDel->setItem(rowNumber,columnNumber+1,new QTableWidgetItem(insertValue1));
        ui->tabDisplayDel->setItem(rowNumber,columnNumber+2,new QTableWidgetItem(insertValue2));
        ui->tabDisplayDel->setItem(rowNumber,columnNumber+3,new QTableWidgetItem(insertValue3));
        ui->tabDisplayDel->setItem(rowNumber,columnNumber+4,new QTableWidgetItem(insertValue4));
        ui->tabDisplayDel->setItem(rowNumber,columnNumber+5,new QTableWidgetItem(insertValue5));
        ui->tabDisplayDel->setItem(rowNumber,columnNumber+6,new QTableWidgetItem(insertValue6));
        ui->tabDisplayDel->setItem(rowNumber,columnNumber+7,new QTableWidgetItem(insertValue7));
        ui->tabDisplayDel->setItem(rowNumber,columnNumber+8,new QTableWidgetItem(insertValue8));

        rowNumber++;

    }


    db.close();
}



void MainWindow::on_tabDisplayDel_cellClicked(int row, int column)
{
    // qDebug() << row << column;
}


//删除槽函数
void MainWindow::on_btnDelFromList_clicked()
{
    int rowNumber = ui->tabDisplayDel->currentItem()->row();
    int columnNumber = ui->tabDisplayDel->currentItem()->column();

//    int rowCo = ui->tabDisplayDel->columnCount() - 5;

//    for(int i=0;i < rowCo;i++)
//    {
//        qDebug()<<(ui->tabDisplayDel->item(rr,i)->text())<<endl;
//    }

    QString usernameForDel = ui->tabDisplayDel->item(rowNumber,0)->text();
    QString userIDForDel = ui->tabDisplayDel->item(rowNumber,1)->text();

    QMessageBox msgBoxDel;
    msgBoxDel.setIcon(QMessageBox::Information);
    msgBoxDel.setWindowTitle("确认删除");
    msgBoxDel.setText(usernameForDel);

    msgBoxDel.setStandardButtons(QMessageBox::Yes | QMessageBox::No);

    int ret = msgBoxDel.exec();

    switch (ret) {
    case QMessageBox::Yes:
    {
        QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
        db.setHostName("localhost");
        db.setDatabaseName("ArchivesManagementSystem");
        db.setUserName("root");
        db.setPassword("ma2015");
        if (!db.open())
            qDebug() << "Failed to connect to root mysql admin";

        QSqlQuery query(db);
        query.prepare("delete from baseinfor where userID=:id");
        query.bindValue(":id",userIDForDel);

        query.exec();
        for(int i=0;i<9;i++)
            ui->tabShowInformation->setItem(rowNumber,i,new QTableWidgetItem(" "));

        qDebug() << "Yes";
        break;
    }
    case QMessageBox::No:
        qDebug() << "No";
        break;
    }
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_action_3_triggered()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("ArchivesManagementSystem");
    db.setUserName("root");
    db.setPassword("ma2015");
    if (!db.open())
        //  qDebug() << "Failed to connect to root mysql admin";
        QMessageBox::warning(this,tr("警告"),("请确认数据库服务是否启动"),QMessageBox::Yes);

    QSqlQuery query(db);


    query.exec("select * from privateinfor");
    int rowNumber = 0,columnNumber = 0;
    while(query.next())
    {
        ui->tabDatail->setRowCount(50);
        ui->tabDatail->setColumnCount(7);

        ui->tabDatail->setColumnWidth(1,150);
        ui->tabDatail->setColumnWidth(3,240);


        QString insertValue0,insertValue1,insertValue2;
        QString insertValue3,insertValue4;
        QString insertValue5;
//        QString insertValue5,insertValue6;
//        QString insertValue7;
//        QString insertValue8;

        insertValue0 = query.value(0).toString();
        insertValue1 = query.value(1).toString();
        insertValue2 = query.value(2).toString();
        insertValue3 = query.value(3).toString();
        insertValue4 = query.value(4).toString();
        insertValue5 = query.value(5).toString();
//        insertValue6 = query.value(6).toString();
//        insertValue7 = query.value(7).toString();
//        insertValue8 = query.value(8).toString();

        ui->tabDatail->setItem(rowNumber,columnNumber,new QTableWidgetItem(insertValue0));
        ui->tabDatail->setItem(rowNumber,columnNumber+1,new QTableWidgetItem(insertValue1));
        ui->tabDatail->setItem(rowNumber,columnNumber+2,new QTableWidgetItem(insertValue2));
        ui->tabDatail->setItem(rowNumber,columnNumber+3,new QTableWidgetItem(insertValue3));
        ui->tabDatail->setItem(rowNumber,columnNumber+4,new QTableWidgetItem(insertValue4));
        ui->tabDatail->setItem(rowNumber,columnNumber+5,new QTableWidgetItem(insertValue5));


        rowNumber++;
    }
    db.close();



    ui->stackedWidget->setCurrentIndex(3);

}

void MainWindow::on_action_2_triggered()
{

//    QDialog *base = new QDialog();
//    base->resize(500,500);
//    QLabel *labName = new QLabel(base);
//    QLabel *labID = new QLabel(base);
//    QLabel *labSalary= new QLabel(base);
//    QLabel *labCardID = new QLabel(base);
//    QLabel *labage = new QLabel(base);
//    QLabel *labPosition = new QLabel(base);

//    QVBoxLayout *bvDialog = new QVBoxLayout(base);
//    bvDialog->addWidget(labName);
//    bvDialog->addWidget(labID);
//    bvDialog->addWidget(labSalary);
//    bvDialog->addWidget(labCardID);
//    bvDialog->addWidget(labage);
//    bvDialog->addWidget(labPosition);


   // base->show();
    int rowNumber = ui->tabShowInformation->currentItem()->row();
    //int columnNumber = ui->tabShowInformation->currentItem()->column();

    //QString username = ui->tabShowInformation->item(rowNumber,0)->text();
    QString userID = ui->tabShowInformation->item(rowNumber,1)->text();

     qDebug() << userID ;



    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("ArchivesManagementSystem");
    db.setUserName("root");
    db.setPassword("ma2015");
    if (!db.open())
        qDebug() << "Failed to connect to root mysql admin";

    QSqlQuery query(db);

    userID.prepend('\"');
    userID.prepend( "select * from privateinfor where userID=");
    userID.append('\"');
    query.exec(userID);

    QString value0,value1,value2;
    QString value3,value4;
    QString value5;
    while(query.next())
    {

        value0 = query.value(0).toString();
        value1 = query.value(1).toString();
        value2 = query.value(2).toString();
        value3 = query.value(3).toString();
        value4 = query.value(4).toString();
        value5 = query.value(5).toString();



        QDialog *base = new QDialog();
        base->resize(500,500);

        QLabel *labName = new QLabel(base);
        QLabel *labID = new QLabel(base);
        QLabel *labSalary= new QLabel(base);
        QLabel *labCardID = new QLabel(base);
        QLabel *labage = new QLabel(base);
        QLabel *labPosition = new QLabel(base);




        labName->setText(value0);
        labID->setText(value1);
        labSalary->setText(value2);
        labCardID->setText(value3);
        labage->setText(value4);
        labPosition->setText(value5);

        QVBoxLayout *bvDialog = new QVBoxLayout(base);
        bvDialog->addWidget(labName);
        bvDialog->addWidget(labID);
        bvDialog->addWidget(labSalary);
        bvDialog->addWidget(labCardID);
        bvDialog->addWidget(labage);
        bvDialog->addWidget(labPosition);


        base->show();

        qDebug() << value0 ;
        qDebug() << value1 ;
        qDebug() << value2 ;
        qDebug() << value3 ;
        qDebug() << value4 ;
        qDebug() << value5 ;
    }


  //  ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_btnAddAdmin_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
}

void MainWindow::on_pushButton_3_clicked()
{

    QString insertAdminUserName;
    QString insertAdminUserID;
    QString insertAdminUserLoginName;
    QString insertAdminUserPasswd;

    insertAdminUserName = ui->editAddAdminUserName->text();
    insertAdminUserID = ui->editAdminUserID->text();
    insertAdminUserLoginName = ui->editAdminLoginName->text();
    insertAdminUserPasswd = ui->editAdminUserPasswd->text();
//    qDebug() << insertAdminUserName;
//    qDebug() << insertAdminUserID;
//    qDebug() << insertAdminUserLoginName;
//    qDebug() << insertAdminUserPasswd;


    while(insertAdminUserName.isEmpty())
    {
        QMessageBox::warning(this,tr("警告"),("请输入姓名"),QMessageBox::Yes);
        ui->editname->setFocus();
        break;
    }
    while(insertAdminUserID.isEmpty())
    {
        QMessageBox::warning(this,tr("警告"),("请输入ID"),QMessageBox::Yes);
        ui->editID->setFocus();
        break;
    }
    while(insertAdminUserLoginName.isEmpty())
    {
        QMessageBox::warning(this,tr("警告"),("请输入登录名"),QMessageBox::Yes);
        ui->editNation->setFocus();
        break;
    }
    while(insertAdminUserPasswd.isEmpty())
    {
        QMessageBox::warning(this,tr("警告"),("请输入密码"),QMessageBox::Yes);
        ui->editPlace->setFocus();
        break;
    }

    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("ArchivesManagementSystem");
    db.setUserName("root");
    db.setPassword("ma2015");
    if (!db.open())
        qDebug() << "Failed to connect to root mysql admin";

    QSqlQuery query(db);



    bool isAllWriting = !(insertAdminUserName.isEmpty()) && !(insertAdminUserID.isEmpty()) && !(insertAdminUserLoginName.isEmpty()) && !(insertAdminUserPasswd.isEmpty());
    if(isAllWriting)
    {

        query.prepare("insert into admin_user(username,userID,userLoginName,userPasswd)"
                      "values(:username,:userID,:userLoginName,:userPasswd)");
        query.bindValue(":username",insertAdminUserName);
        query.bindValue(":userID",insertAdminUserID);
        query.bindValue(":userLoginName",insertAdminUserLoginName);
        query.bindValue(":userPasswd",insertAdminUserPasswd);
        if(query.exec())
        {
            QMessageBox::information(this,tr("通知"),("添加成功"),QMessageBox::Yes);
            ui->stackedWidget->setCurrentIndex(0);


            ui->editAddAdminUserName->clear();
            ui->editAdminUserID->clear();
            ui->editAdminLoginName->clear();
            ui->editAdminUserPasswd->clear();

        }
    }



    db.close();

   // ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_pushButton_4_clicked()
{
    ui->editAddAdminUserName->clear();
    ui->editAdminUserID->clear();
    ui->editAdminLoginName->clear();
    ui->editAdminUserPasswd->clear();
    ui->stackedWidget->setCurrentIndex(0);
}
