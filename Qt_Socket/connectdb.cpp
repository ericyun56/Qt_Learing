#include "connectdb.h"


bool connDB()
{

    qDebug() << "Available drivers:";
    QStringList drivers = QSqlDatabase::drivers();
    foreach(QString driver, drivers)
        qDebug() << driver;

    // 打开MySQL
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("ArchivesManagementSystem");
    db.setUserName("root");
    db.setPassword("ma2015");
    if (!db.open())
        qDebug() << "Failed to connect to root mysql admin";
    else qDebug() << "open";

    QSqlQuery query(db);

    //    //注意这里varchar一定要指定长度，不然会出错
    //    query.exec("create table student(id int primary key,name varchar(20))");

    //    query.exec("insert into student values(1,'xiaogang')");
    //    query.exec("insert into student values(2,'xiaoming')");
    //    query.exec("insert into student values(3,'xiaohong')");

    //    query.exec("select id,name from student where id >= 1");
    query.exec("select * from baseinfor");
    while(query.next())
    {
        int value0 = query.value(0).toInt();
        QString value1 = query.value(1).toString();
        // QString value2 = query.value(2).toString();
        qDebug() << value0 << value1 ;
    }
    //    query.exec("SELECT VERSION()");
    //    while(query.next())
    //    {

    //        QString value0 = query.value(0).toString();

    //        qDebug() << value0  ;
    //    }


    //        query.exec("SELECT CURRENT_DATE");
    //        while(query.next())
    //        {

    //            QString value0 = query.value(0).toString();

    //            qDebug() << value0  ;
    //        }
    return 0;
}


