#-------------------------------------------------
#
# Project created by QtCreator 2017-10-23T11:12:16
#
#-------------------------------------------------

QT       += core gui
QT       += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QSqlQueryModelCrud
TEMPLATE = app


SOURCES += main.cpp\
        ManWin.cpp \
    SelfSqlQueryModel.cpp

HEADERS  += ManWin.h \
    QSqliteConnect.h \
    SelfSqlQueryModel.h

FORMS    += ManWin.ui
