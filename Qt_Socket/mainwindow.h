#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMainWindow>
#include <QTimer>
#include <QTime>
#include <QDate>
#include <QListWidgetItem>
#include <QCalendarWidget>
#include "connectdb.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    bool getNameFromDB();
    bool getIDFromDB();
    bool getDepartmentFromDB();
    bool getNameFromDB_Del();
    bool getIDFromDB_Del();
    bool getDepartmentFromDB_Del();

private slots:
    void qtimeSlot_2();  
    void on_comIndex_currentIndexChanged(int index);

    void on_btnSearch_clicked();

    void on_editIndex_editingFinished();

    void on_listIndex_itemClicked(QListWidgetItem *item);

    void on_btnPageAdd_clicked();

    void on_btnPageDel_clicked();

    void on_btnAdd_clicked();

    void on_btnDel_clicked();

    void on_commandChoose_clicked();

    void on_commandFinish_clicked();

    void on_pushButton_clicked();

    void on_btnDetail_clicked();

    void on_btnAddToDataBase_clicked();

    void on_btnReset_clicked();

    void on_pushButton_2_clicked();

    void on_btnPageDelVerify_clicked();

    void on_comIndexDel_currentIndexChanged(int index);

    void on_listIndexDel_clicked(const QModelIndex &Oindex);

    void on_tabDisplayDel_cellClicked(int row, int column);

    void on_btnDelFromList_clicked();

    void on_action_3_triggered();

    void on_action_2_triggered();

    void on_btnAddAdmin_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::MainWindow *ui;
    int g_nActScreenW;
    int g_nActScreenH;
    QTimer *timer_2;
    QCalendarWidget *calender;
};

#endif // MAINWINDOW_H
