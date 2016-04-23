#include "mainwindow.h"
#include <QApplication>
#include <QDialog>
#include "logindialog.h"
#include <QTextCodec>
#include <QMessageBox>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    MainWindow w;
    // w.show();

    LoginDialog mLogin;

    QMessageBox msgBox;
    msgBox.setIcon(QMessageBox::Information);
    msgBox.setWindowTitle("系统启动");
    msgBox.setText("系统已启动");
    //msgBox.setInformativeText("系统已启动");
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
   // msgBox.setDefaultButton(QMessageBox::Save);
    int ret = msgBox.exec();

    switch (ret) {
    case QMessageBox::Yes:
        if(mLogin.exec() == QDialog::Accepted)
        {
            w.show();          // 如果被按下，显示主窗口
            return a.exec();      // 程序一直执行，直到主窗口关闭
        }
        else
            return 0;
        break;
    case QMessageBox::No:
        a.closeAllWindows();
        break;
    default:
        // should never be reached
        break;
}



    return a.exec();
}
