#-------------------------------------------------
#
# Project created by QtCreator 2016-10-30T12:52:31
#
#-------------------------------------------------

QT       += core gui concurrent
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = oko
TEMPLATE = app


SOURCES += src/main.cpp\
        src/mainwindow.cpp \
    src/genBoardInterface.cpp \

HEADERS  += src/mainwindow.h \
    src/genBoardInterface.h \

FORMS    += src/mainwindow.ui
