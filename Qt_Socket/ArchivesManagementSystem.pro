#-------------------------------------------------
#
# Project created by QtCreator 2016-04-16T15:40:01
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ArchivesManagementSystem
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    logindialog.cpp \
    connectdb.cpp

HEADERS  += mainwindow.h \
    logindialog.h \
    connectdb.h

FORMS    += mainwindow.ui \
    logindialog.ui

RESOURCES += \
    sourcefile.qrc
