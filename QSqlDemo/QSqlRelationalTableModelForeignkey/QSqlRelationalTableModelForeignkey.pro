#-------------------------------------------------
#
# Project created by QtCreator 2017-10-25T17:03:56
#
#-------------------------------------------------

QT       += core gui
QT       += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QSqlRelationalTableModelForeignkey
TEMPLATE = app


SOURCES += main.cpp\
        MainWin.cpp

HEADERS  += MainWin.h \
    QSqliteConnect.h

FORMS    += MainWin.ui
