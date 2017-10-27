#-------------------------------------------------
#
# Project created by QtCreator 2017-10-24T13:59:01
#
#-------------------------------------------------

QT       += core gui
QT       += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QSqlTableModelCrud
TEMPLATE = app


SOURCES += main.cpp\
        ManWin.cpp

HEADERS  += ManWin.h \
    QSqliteConnect.h

FORMS    += ManWin.ui
