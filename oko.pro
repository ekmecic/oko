#-------------------------------------------------
#
# Project created by QtCreator 2016-10-30T12:52:31
#
#-------------------------------------------------

QT       += core gui concurrent
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = oko
TEMPLATE = app


SOURCES += src/main.cpp\
        src/mainwindow.cpp \
    src/genBoardInterface.cpp \
    lib/qcustomplot/qcustomplot.cpp

HEADERS  += src/mainwindow.h \
    src/genBoardInterface.h \
    lib/qcustomplot/qcustomplot.h

FORMS    += src/mainwindow.ui
