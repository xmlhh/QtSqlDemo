#-------------------------------------------------
#
# Project created by QtCreator 2017-10-23T10:16:44
#
#-------------------------------------------------

QT       += core gui
QT       += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QSqliteCrud
TEMPLATE = app


SOURCES += main.cpp\
        ManWin.cpp

HEADERS  += ManWin.h \
    QSqliteConnect.h

FORMS    += ManWin.ui
